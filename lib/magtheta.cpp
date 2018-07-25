#include "../include/magtheta.h"
#include "../include/data.h"
#include "../include/green.h"
#include "../include/pauli.h"
#include <vector>
#include <cmath>

MagTheta::MagTheta(std::string data_folder, Limits _lim) : \
  inDataU(data_folder, 1, 12, _lim), \
  inDataD(data_folder, 1, 12, _lim), \
  lim(_lim) {
  lim.spin = 1;
  inDataU = InData(data_folder, 1, 12, lim);
  lim.spin = 0;
  inDataD = InData(data_folder, 0, 12, lim);
}

double MagTheta::simpFac(int value, int max) {
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

std::vector<double> MagTheta::compute(int order) {
  std::vector<double> \
    ener = lim.space(0), \
    kPol = lim.space(1), \
    kAzi = lim.space(2);
  int i, j, k, l;
  std::complex<double> hE, hXi, hTheta;
  Pauli P;
  mat G;
  std::vector<double> rv;
  for (k=0; k<lim.kAzimuN; k++) {
    hTheta = 0.0;
    for (i=0; i<lim.energyN; i++) {
      hE = 0.0;
      for (j=0; j<lim.kPolarN; j++) {
	hXi = 0.0;
	G = mat::Zero();
	for (l=0; l<order+1; l++) {
	  G += inDataU.get(l, i, j, k);
	  G -= inDataD.get(l, i, j, k);
	}
	hXi += (P.get(3) * G).trace();
	hXi /= 4 * M_PI;
	hXi *= sin(kPol[j]) * lim.kPolarD * 3.0 / 10.0;
	hXi *= simpFac(j, lim.kPolarN);
	hE += hXi;
      }
      hE *= lim.energyD;
      hE *= simpFac(i, lim.energyN);
      hTheta += hE;
    }
    rv.push_back(hTheta.imag());
  }
  return rv;
}
