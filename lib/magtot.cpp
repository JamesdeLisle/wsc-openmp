#include "../include/magtot.h"
#include "../include/data.h"
#include "../include/green.h"
#include "../include/pauli.h"
#include <vector>
#include <cmath>

Magnetisation::Magnetisation(std::string data_folder, Limits _lim) : \
  inDataU(data_folder, 1, 12, _lim), \
  inDataD(data_folder, 1, 12, _lim), \
  lim(_lim) {
  lim.spin = 1;
  inDataU = InData(data_folder, 1, 12, lim);
  lim.spin = 0;
  inDataD = InData(data_folder, 0, 12, lim);
}

double simpFac(int value, int max) {
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

double Magnetisation::compute(int order) {
  std::vector<double> \
    ener = lim.space(0), \
    kPol = lim.space(1), \
    kAzi = lim.space(2);
  int i, j, k, l;
  std::complex<double> hE, hXi, hTheta, rv;
  Pauli P;
  mat G;
  double MAX = 0.0;
  rv = 0.0;
  for (i=0; i<lim.energyN; i++) {
    hE = 0.0;
    for (j=0; j<lim.kPolarN; j++) {
      hXi = 0.0;
      for (k=0; k<lim.kAzimuN; k++) {
	hTheta = 0.0;
	G = mat::Zero();
	for (l=0; l<order+1; l++) {
	  G += inDataU.get(l, i, j, k);
	  //G -= inDataD.get(l, i, j, k);
	}
	hTheta += (P.get(3) * G).trace();
	hTheta /= (8 * M_PI * M_PI);
	hTheta *= lim.kAzimuD;
	hTheta *= simpFac(k, lim.kAzimuN);
	hXi += hTheta;
      }
      hXi *= sin(kPol[j]) * lim.kPolarD;
      hXi *= simpFac(j, lim.kPolarN);
      hE += hXi;
      if (hXi.imag() > MAX) {
	MAX = hXi.imag();
      }
    }
    std::cout << MAX << std::endl;
    hE *= lim.energyD;
    hE *= simpFac(i, lim.energyN);
    rv += hE;
  }
  return rv.imag();
}
