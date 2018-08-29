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
#include <complex>
#include <fstream>
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

void Space::run(std::string _data_folder, std::ofstream * flog) {
  int i, j, k;
  InData inData(_data_folder, lim.spin, order, lim);
  for (i=0; i<lim.energyN; i++) {
    for (j=0; j<lim.kPolarN; j++) {
      #pragma omp parallel for schedule(static)
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

// Redundant function,
double Space::getDelSq(std::string _data_folder) {
  int j, k;
  double val, min = 10.0;
  for (j=0; j<lim.kPolarN; j++) {
    for (k=0; k<lim.kAzimuN; k++) {
      int idxv[3] = {0, j, k};
      std::vector<int> idx(idxv,  idxv + sizeof(idxv) / sizeof(int));
      RunVal entry(1.0, kPolar.at(j), kAzimu.at(k), idx, lim);
      Environment E(entry);
      val = abs(E.getDeltaR());
      if (val < min) {
	min = val;
      }
    }
  }
  return min;
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
