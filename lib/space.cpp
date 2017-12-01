#include "../include/space.h"
#include "../include/green.h"
#include "../include/limits.h"
#include "../include/data.h"
#include "../include/env.h"
#include "../include/data.h"
#include "../include/pauli.h"

#include "../include/kernel.h"
#include <vector>
#include <iostream>
#include <string>
#include "omp.h"

namespace SPACE {
  std::vector<double> linspace(double min, double max, int disc) {
    int i;
    std::vector<double> rv;
    double step = (max - min) / disc;
    for (i=0; i<disc-1; i++) {
      rv.push_back(min + step * i);
    }
    rv.push_back(max);
    return rv;
  }
}

RunVal::RunVal(double energy,
	       double kPolar,
	       double kAzimu,
	       std::vector<int> idx,
	       Limits L) : lim(L){
  E = energy;
  Xi = kPolar;
  Theta = kAzimu;
  lim = L;
  index = idx;
  alpha = L.alpha;
  iAlpha = 0;
}

Space::Space(Limits L, std::string _time,
	     int _order) : lim(L), runData(Data(L, _time, _order)) {
  lim = L;
  time = _time;
  order = _order;
  energy = SPACE::linspace(L.energyMin, L.energyMax, L.energyN);
  kPolar = SPACE::linspace(L.kPolarMin, L.kPolarMax, L.kPolarN);
  kAzimu = SPACE::linspace(L.kAzimuMin, L.kAzimuMax, L.kAzimuN);
  runData = Data(lim, time, order);
}

void Space::progress(int i, int j) {
  std::cout << "\r" << (int) ((100.0 * ((i + 1) * lim.kPolarN + j))
			      / (lim.energyN * lim.kPolarN)) << "%";
  std::cout.flush();
}

void Space::run(std::string _data_folder) {
  int i, j, k;
  InData inData(_data_folder, lim.spin, order, lim);
  int max_threads = omp_get_max_threads();
  omp_set_num_threads(25);
  std::cout << "Computing order: " << order << "..." << std::endl;
  for (i=0; i<lim.energyN; i++) {
    for (j=0; j<lim.kPolarN; j++) {
      this->progress(i, j);
      //#pragma omp parallel for schedule(static)
      for (k=0; k<lim.kAzimuN; k++) {
	int idxv[3] = {i, j, k};
	std::vector<int> idx(idxv,  idxv + sizeof(idxv) / sizeof(int));
	RunVal entry(energy.at(i), kPolar.at(j), kAzimu.at(k), idx, lim);
	kernel(i, j, k, order, entry, &inData, runData);
      }
    }
  }
  std::cout << std::endl;
  runData.write(_data_folder);
}

double Space::simpFac(int value, int max) {
  if (value == 0 || value  == max - 1) {
    return 1.0;
  }
  else if (value % 2 == 0) {
    return 4.0;
  }
  else {
    return 2.0;
  }
}

void Space::test(std::string _data_folder) {
  int i, j, k, s;
  InData inData(_data_folder, lim.spin, order, lim);
  std::vector<Data> dat;
  lim.spin = 0;
  Data U(lim, time, 0);
  lim.spin = 1;
  Data D(lim, time, 0);
  dat.push_back(U);
  dat.push_back(D);
  std::cout << "Computing order: " << order << "..." << std::endl;
  for (s=0; s<2; s++) {
    for (i=0; i<lim.energyN; i++) {
      for (j=0; j<lim.kPolarN; j++) {
	this->progress(i, j);
	for (k=0; k<lim.kAzimuN; k++) {
	  int idxv[3] = {i, j, k};
	  std::vector<int> idx(idxv,  idxv + sizeof(idxv) / sizeof(int));
	  RunVal entry(energy.at(i), kPolar.at(j), kAzimu.at(k), idx, lim);
	  kernel(i, j, k, order, entry, &inData, dat[s]);
	}
      }
    }
  }
  std::vector<double> \
    ener = lim.space(0), \
    kPol = lim.space(1), \
    kAzi = lim.space(2);
  int l;
  std::complex<double> hTheta, I(0.0, 1.0);
  double hE, hXi;
  Pauli P;
  mat G; 
  std::vector<double> rv;
  for (i=0; i<lim.energyN; i++) {
    hE = 0.0;
    for (j=0; j<lim.kPolarN; j++) {
      hXi = 0.0;
      for (k=0; k<lim.kAzimuN; k++) {
	hTheta = 0.0;
	G = mat::Zero();
	G += dat[0].get(i, j, k);
	hTheta += 1.0 * I / (4.0 * M_PI * M_PI);
	hTheta *= 0.5 * (P.get(3) * G).trace();
	hTheta *= lim.kAzimuD / 3.0;
	hTheta *= simpFac(k, lim.kAzimuN);
	hXi += hTheta.imag();
      }
      hXi *= sin(kPolar[j]) * lim.kPolarD / 3.0;
      hXi *= simpFac(j, lim.kPolarN);
      hE += hXi;
    }
    std::cout << hE << std::endl;
  }
}
