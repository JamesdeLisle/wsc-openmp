#include "../include/dos.h"
#include "../include/data.h"
#include "../include/green.h"
#include "../include/pauli.h"
#include <vector>
#include <cmath>
#include <stdlib.h>

DOS::DOS(std::string data_folder, Limits _lim) :	\
  inDataU(data_folder, 1, 11, _lim), \
  inDataD(data_folder, 1, 11, _lim), \
  lim(_lim) {
  lim.spin = 1;
  inDataU = InData(data_folder, 1, 11, lim);
  lim.spin = 0;
  inDataD = InData(data_folder, 0, 11, lim);
}

double DOS::simpFac(int value, int max) {
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

std::vector<double> DOS::compute(int order) {
  std::vector<double> \
    ener = lim.space(0), \
    kPol = lim.space(1), \
    kAzi = lim.space(2);
  int i, j, k, l;
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
	for (l=0; l<order+1; l++) {
	  G += inDataU.get(l, i, j, k);
	  //G -= inDataD.get(l, i, j, k);
	}
	/*std::cout << G << std::endl;
	std::cout << "............" << std::endl;
	std::cout << inDataU.get(0, i, j, k) << std::endl;
	std::cout << "............" << std::endl;
	std::cout << inDataD.get(0, i, j, k) << std::endl;
	std::cout << "############" << std::endl;*/
	hTheta += 1.0 * I / (4.0 * M_PI * M_PI);
	hTheta *= 0.5 * (P.get(3) * G).trace();
	hTheta *= lim.kAzimuD / 3.0;
	hTheta *= DOS::simpFac(k, lim.kAzimuN);
	hXi += hTheta.imag();
      }
      hXi *= sin(kPol[j]) * lim.kPolarD / 3.0;
      hXi *= DOS::simpFac(j, lim.kPolarN);
      hE += hXi;
    }
    rv.push_back(hE);
  }
  return rv;
}
