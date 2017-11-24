#include "../include/magtot.h"
#include "../include/data.h"
#include "../include/green.h"
#include <vector>

Magnetisation::Magnetisation(std::string data_folder, Limits _lim) : \
  inData(data_folder, 10, lim), lim(_lim) {
}

double Magnetisation::compute() {
  /*
  std::vector<double>	 \
    ener = lim.space(0), \
    kPol = lim.space(1), \
    kAzi = lim.space(2);
  int i, j, k;
  double hE, hXi, hTheta, rv;
  mat G; 
  rv = 0.0;
  for (i=0; i<lim.energyN; i++) {
    hE = 0.0;
    for (j=0; j<lim.kPolarN; j++) {
      for (k=0; k<lim.kAzimuN; k++) {
      }
    }
  }
  */
}
