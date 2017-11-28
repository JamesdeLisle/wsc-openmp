#include "../include/magtot.h"
#include "../include/data.h"
#include "../include/green.h"
#include "../include/pauli.h"
#include <vector>
#include <cmath>

Magnetisation::Magnetisation(std::string data_folder, Limits _lim) : \
  inDataU(data_folder, 1, 10, _lim), \
  inDataD(data_folder, 1, 10, _lim), \
  lim(_lim) {
  lim.spin = 1;
  inDataU = InData(data_folder, 1, 10, lim);
  lim.spin = 0;
  inDataD = InData(data_folder, 0, 10, lim);
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

double Magnetisation::compute() {
  std::vector<double> \
    ener = lim.space(0), \
    kPol = lim.space(1), \
    kAzi = lim.space(2);
  int i, j, k, l;
  std::complex<double> hE, hXi, hTheta, rv;
  Pauli P;
  mat G; 
  rv = 0.0;
  for (i=0; i<lim.energyN; i++) {
    hE = 0.0;
    for (j=0; j<lim.kPolarN; j++) {
      hXi = 0.0;
      for (k=0; k<lim.kAzimuN; k++) {
	hTheta = 0.0;
	G = mat::Zero();
	for (l=0; l<4; l++) {
	  G += inDataU.get(l, i, j, k);
	  //G -= inDataD.get(l, i, j, k);
	}
	hTheta += (P.get(3) * G).trace();
	hTheta /= (8 * M_PI * M_PI);
	hTheta *= lim.kAzimuD;
	hTheta *= simpFac(k, lim.kAzimuN);
	hXi += hTheta;
      }
      hXi *= sin(kPol[j]) * lim.kPolarN * 3.0 / 8.0;
      hXi *= simpFac(j, lim.kPolarN);
      hE += hXi;
    }
    hE += lim.energyN * 3.0 / 8.0;
    hE *= simpFac(i, lim.energyN);
    rv += hE;
  }
  return rv.imag();
}
