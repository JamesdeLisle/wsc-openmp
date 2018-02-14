#include "../include/green.h"
#include "../include/space.h"
#include "../include/env.h"
#include "../include/quantumb.h"
#include <eigen3/Eigen/Dense>
#include <complex>
#include <cmath>
#include "../include/pauli.h"

Quantumb::Quantumb(RunVal _runVal,
		   mat _ret1,
		   mat _dpzret1,
		   mat _dthetakel2) :		\
  runVal(_runVal),				\
  ret1(_ret1),					\
  dpzret1(_dpzret1),				\
  dthetakel2(_dthetakel2) {}

Green Quantumb::get(Green funcVal) {
  Pauli P;
  std::complex<double> I(0.0, 1.0);
  mat rvm;
  mat adv1 = P.get(3) * ret1.adjoint() * P.get(3);
  mat dpzadv1 = P.get(3) * dpzret1 * P.get(3);
  runVal.comp();
  Environment E(runVal);
  double sgn, pi = M_PI;
  if (runVal.getXi() < pi / 2) {
    sgn = 1.0;
  }
  else {
    sgn = -1.0;
  }
  
  rvm = (E.epsi().get() - E.hamR().get()) * funcVal.get() -	\
    funcVal.get() * (E.epsi().get() - E.hamA().get()) +		\
    ret1 * E.hamKG().get() - E.hamKG().get() * adv1 -		\
    (I / 2.0) * dpzret1 * E.dzhamKG().get() -			\
    (I / 2.0) * E.dzhamKG().get() * dpzadv1 +			\
    sgn * I * runVal.getlim()->magF * dthetakel2;

  Green rv(-rvm / runVal.getlim()->fermV);
  return rv; 
}

Green Quantumb::bound() {
  Environment E(runVal);
  Pauli P;
  mat rvm = (ret1 - P.get(3) * ret1.adjoint() * P.get(3)) * E.getThermDG();
  Green rv(rvm);
  return rv;
}
