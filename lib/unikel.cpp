#include "../include/green.h"
#include "../include/space.h"
#include "../include/env.h"
#include "../include/unikel.h"
#include <eigen3/Eigen/Dense>
#include "../include/pauli.h"
#include <complex>

UniKel::UniKel(RunVal _runVal, mat _ret0) : \
  runVal(_runVal), ret0(_ret0) {
}

Green UniKel::get(Green funcVal) {
  mat rvm;
  Pauli P;
  std::complex<double> I(0.0, 1.0);
  runVal.comp();
  Environment E(runVal);
  mat adv0 = P.get(3) * ret0.adjoint() * P.get(3);
  rvm = funcVal.get() * (E.epsi().get() - E.hamA().get()) -	\
    (E.epsi().get() - E.hamR().get()) * funcVal.get() +		\
    ret0 * E.hamKG().get() - E.hamKG().get() * adv0;
  Green rv(-I * rvm / runVal.getlim()->fermV);
  return rv; 
}

Green UniKel::bound() {
  mat rvm;
  Pauli P;
  runVal.comp();
  Environment E(runVal);
  rvm = (ret0 - P.get(3) * ret0.adjoint() * P.get(3)) * E.getThermDG();
  //rvm = mat::Zero();
  Green rv(rvm);
  return rv;
}
