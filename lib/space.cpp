#include "../include/space.h"
#include "../include/green.h"
#include "../include/limits.h"
#include "../include/data.h"
#include "../include/env.h"
#include "../include/data.h"

#include "../include/kernel.h"
#include <vector>
#include <iostream>
#include <string>
#include "omp.h"

std::vector<double> linspace(double min, double max, int disc) {
  int i;
  std::vector<double> rv;
  double step = (max - min) / (disc-1);
  for (i=0; i<disc-1; i++) {
    rv.push_back(min + step * i);
  }
  rv.push_back(max);
  return rv;
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
  energy = linspace(L.energyMin, L.energyMax, L.energyN);
  kPolar = linspace(L.kPolarMin, L.kPolarMax, L.kPolarN);
  kAzimu = linspace(L.kAzimuMin, L.kAzimuMax, L.kAzimuN);
  runData = Data(lim, time, order);
}

void Space::progress(int i, int j) {
  std::cout << "\r" << (int) (100.0 * (i * (lim.kPolarN - 2) + j))	\
    / ((lim.energyN - 1) * (lim.kPolarN - 1)) << "%";
  std::cout.flush();
}

void Space::run(std::string _data_folder) {
  int i, j, k;
  InData inData(_data_folder, order, lim);
  int max_threads = omp_get_max_threads();
  omp_set_num_threads(max_threads-4);
  std::cout << "Computing order: " << order << "..." << std::endl;
  for (i=0; i<lim.energyN; i++) {
    for (j=0; j<lim.kPolarN; j++) {
      //this->progress(i, j);
      std::cout << i << " " << j << std::endl;
      #pragma omp parallel for schedule(static)
      for (k=0; k<lim.kAzimuN; k++) {
	int idxv[3] = {i, j, k};
	std::vector<int> idx(idxv,  idxv + sizeof(idxv) / sizeof(int));
	RunVal entry(energy.at(i), kPolar.at(j), kAzimu.at(k), idx, lim);
	kernel(i, j, k, order, entry, inData, runData);
      }
    }
  }
  std::cout << std::endl;
  runData.write(_data_folder);
}
