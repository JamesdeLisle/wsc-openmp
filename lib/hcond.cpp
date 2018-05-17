#include "../include/hcond.h"
#include "../include/data.h"
#include "../include/green.h"
#include "../include/pauli.h"
#include <vector>
#include <cmath>

HeatCond::HeatCond(std::string data_folder, Limits _lim) : \
  inDataU(data_folder, 1, 12, _lim), \
  inDataD(data_folder, 1, 12, _lim), \
  lim(_lim) {
  lim.spin = 1;
  inDataU = InData(data_folder, 1, 12, lim);
  lim.spin = 0;
  inDataD = InData(data_folder, 0, 12, lim);
}

double HeatCond::simpFac(int value, int max) {
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

std::vector<double> HeatCond::compute() {
  std::vector<double> \
    ener = lim.space(0), \
    kPol = lim.space(1), \
    kAzi = lim.space(2);
  int i, j, k, l;
  std::vector<double> rv;
  std::complex<double> hEU, hXiU, hThetaU, hED, hXiD, hThetaD;
  Pauli P;
  mat GU, GD; 
  rv.push_back(0.0);
  rv.push_back(0.0);
  for (i=0; i<lim.energyN; i++) {
    hEU = 0.0;
    hED = 0.0;
    for (j=0; j<lim.kPolarN; j++) {
      hXiU = 0.0;
      hXiD = 0.0;
      for (k=0; k<lim.kAzimuN; k++) {
	hThetaU = 0.0;
	hThetaD = 0.0;
	GU = mat::Zero();
	GD = mat::Zero();
	for (l=0; l<2; l++) {
	  GU += inDataU.get(l, i, j, k);
	  GD += inDataD.get(l, i, j, k);
	}
	hThetaU += (P.get(3) * GU).trace();
	hThetaD += (P.get(3) * GU).trace();
	hThetaU *= lim.kAzimuD;
	hThetaD *= lim.kAzimuD;
	hThetaU *= simpFac(k, lim.kAzimuN);
	hThetaD *= simpFac(k, lim.kAzimuN);
	hXiU += hThetaU;
	hXiD += hThetaD;
      }
      hXiU *= sin(kPol[j]) * cos(kPol[j]) * lim.kPolarD;
      hXiD *= sin(kPol[j]) * cos(kPol[j]) * lim.kPolarD;
      hXiU *= simpFac(j, lim.kPolarN);
      hXiD *= simpFac(j, lim.kPolarN);
      hEU += hXiU;
      hED += hXiD;
    }
    hEU *= ener[i] * lim.energyD;
    hED *= ener[i] * lim.energyD;
    hEU *= simpFac(i, lim.energyN);
    hED *= simpFac(i, lim.energyN);
    rv[1] += hEU.imag() / (408 * M_PI);
    rv[0] += hED.imag() / (408 * M_PI);
  }
  return rv;
}
