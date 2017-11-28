#include "../include/green.h"
#include "../include/space.h"
#include "../include/env.h"
#include "../include/quantum.h"
#include <eigen3/Eigen/Dense>
#include <complex>
#include <cmath>
#include "../include/pauli.h"

Quantum::Quantum(RunVal _runVal, mat _ret0, mat _dpzret0) :	\
  runVal(_runVal), ret0(_ret0), dpzret0(_dpzret0) {
}

Green Quantum::get(Green funcVal) {
  Pauli P;
  std::complex<double> I(0.0, 1.0);
  mat rvm;
  mat adv0 = P.get(3) * ret0.adjoint() * P.get(3);
  mat dpzadv0 = P.get(3) * dpzret0 * P.get(3);
  runVal.comp();
  Environment E(runVal);
 
  rvm = (E.epsi().get() - E.hamR().get()) * funcVal.get() - \
    funcVal.get() * (E.epsi().get() - E.hamA().get()) + \
    ret0 * E.hamKG().get() - E.hamKG().get() * adv0 - \
    (I / 2.0) * dpzret0 * E.dzhamKG().get() -	      \
    (I / 2.0) * E.dzhamKG().get() * dpzadv0;

  Green rv(-rvm / runVal.getlim()->fermV);
  return rv; 
}

Green Quantum::bound() {
  Environment E(runVal);
  Pauli P;
  mat rvm = (ret0 - P.get(3) * ret0.adjoint() * P.get(3)) * E.getThermDG();
  Green rv(rvm);
  return rv;
}
