#include "../include/green.h"
#include "../include/space.h"
#include "../include/env.h"
#include "../include/retard.h"
#include <complex>
#include <cmath>


Retarded::Retarded(RunVal _runVal, mat _dg0) : runVal(_runVal), dg0(_dg0) {
  runVal = _runVal;
  dg0 = _dg0;
}

Green Retarded::get() {
  Green rv, tmp;
  std::complex<double> I(0.0, 1.0);
  double sgn, pi = M_PI;
  Environment E(runVal);
  tmp = E.epsi() - E.hamR();
  if (runVal.getXi() < pi / 2) {
    sgn = 1.0;
  }
  else {
    sgn = -1.0;
  }
  
  rv.set(0.5 * (-1.0 / ((runVal.getE() - E.getSigmaR()) *
			(runVal.getE() - E.getSigmaR()) -
			E.getDeltaR() * std::conj(E.getDeltaR()))) *	\
	 tmp.get().inverse() * sgn * runVal.getlim()->magF * I * dg0);
  return rv;
}
