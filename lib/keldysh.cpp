#include "../include/green.h"
#include "../include/space.h"
#include "../include/env.h"
#include "../include/keldysh.h"
#include "../include/keldysh.h"
#include <eigen3/Eigen/Dense>
#include <complex>
#include <cmath>
#include "../include/pauli.h"

Keldysh::Keldysh(RunVal _runVal, mat _ret0, mat _ret1, mat _dkel0) :	\
  runVal(_runVal), ret0(_ret0), ret1(_ret1), dkel0(_dkel0) {
}

Green Keldysh::get(Green funcVal) {
  Pauli P;
  std::complex<double> I(0.0, 1.0);
  double sgn, pi = M_PI;
  mat rvm;
  mat ret = ret1;
  mat adv = P.get(3) * ret.adjoint() * P.get(3);
  runVal.comp();
  Environment E(runVal);
  
  if (runVal.getTheta() < pi) {
    sgn = 1.0;
  }
  else {
    sgn = -1.0;
  }
 
  rvm = funcVal.get() * (E.epsi().get() - E.hamA().get()) -	\
    (E.epsi().get() - E.hamR().get()) * funcVal.get() +		\
    ret * E.hamKG().get() - E.hamKG().get() * adv -		\
    sgn * I * runVal.getlim()->magF * dkel0;

  Green rv(-I * rvm / runVal.getlim()->fermV);
  return rv; 
}

Green Keldysh::bound() {
  mat rvm;
  Pauli P;
  runVal.comp();
  Environment E(runVal);
  rvm = (ret0 - P.get(3) * ret0.adjoint() * P.get(3)) * E.getThermDG();
  Green rv(rvm);
  return rv;
}
