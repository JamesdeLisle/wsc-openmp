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
  Green rv;
  std::complex<double> I(0.0, 1.0);
  double sgn, pi = M_PI;
  Environment E(runVal);
  rv = E.epsi() - E.hamR();
  if (runVal.getXi() < pi / 2) {
    sgn = 1.0;
  }
  else {
    sgn = -1.0;
  }
  
  //std::cout << dg0 << std::endl;
  mat inv;
  inv(0, 0) = rv.get(1, 1);
  inv(0, 1) = -rv.get(1, 0);
  inv(1, 0) = -rv.get(0, 1);
  inv(1, 1) = rv.get(0, 0);
  inv = inv * (1.0 / (rv.get(0, 0) * rv.get(1, 1) - rv.get(0, 1) * rv.get(1, 0)));
  rv.set(-0.5 * inv * sgn * runVal.getlim()->magF * I * dg0);
  return rv;
}
