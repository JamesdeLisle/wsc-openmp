#include "../include/green.h"
#include "../include/space.h"
#include "../include/env.h"
#include "../include/quantumb.h"
#include <eigen3/Eigen/Dense>
#include <complex>
#include <cmath>
#include "../include/pauli.h"

Quantumb::Quantumb(RunVal _runVal, mat _ret0, mat _dpzret1) :	\
  runVal(_runVal), ret0(_ret0), dpzret1(_dpzret1) {
}

Green Quantumb::get(Green funcVal) {
  Pauli P;
  std::complex<double> I(0.0, 1.0);
  mat rvm;
  mat adv0 = P.get(3) * ret0.adjoint() * P.get(3);
  mat dpzadv1 = P.get(3) * dpzret1 * P.get(3);
  runVal.comp();
  Environment E(runVal);
 
  rvm = (E.epsi().get() - E.hamR().get()) * funcVal.get() - \
    funcVal.get() * (E.epsi().get() - E.hamA().get()) + \
    ret0 * E.hamKG().get() - E.hamKG().get() * adv0 - \
    (I / 2.0) * dpzret1 * E.dzhamKG().get() -	      \
    (I / 2.0) * E.dzhamKG().get() * dpzadv1;

  Green rv(-rvm / runVal.getlim()->fermV);
  return rv; 
}

Green Quantumb::bound() {
  mat rvm = mat::Zero();
  Green rv(rvm);
  return rv;
}
