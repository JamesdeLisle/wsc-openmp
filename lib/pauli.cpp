#include "../include/pauli.h"
#include <complex>
#include <eigen3/Eigen/Dense>
#include <iostream>

Pauli::Pauli() {
  std::complex<double> one(1.0, 0.0);
  std::complex<double> I(0.0, 1.0);
  values.resize(4);
  int i;
  for (i=0; i<4; i++) {
    values[i] = mat::Zero();
  }
  values[0](0, 0) = one;
  values[0](1, 1) = one;
  values[0](0, 1) = 0.0;
  values[0](1, 0) = 0.0;
  values[1](0, 1) = one;
  values[1](1, 0) = one;
  values[1](0, 0) = 0.0;
  values[1](1, 1) = 0.0;
  values[2](0, 1) = -I;
  values[2](1, 0) = I;
  values[2](0, 0) = 0.0;
  values[2](1, 1) = 0.0;
  values[3](0, 0) = one;
  values[3](1, 1) = -one;
  values[3](0, 1) = 0.0;
  values[3](1, 0) = 0.0;
}
