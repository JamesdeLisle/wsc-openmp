#include "../include/green.h"
#include "../include/pauli.h"
#include <eigen3/Eigen/Dense>
#include <complex>

Green::Green() {
  matrix = mat::Zero();
}

std::complex<double> Green::getZTrace() {
  Pauli P;
  return (P.get(3) * matrix).trace();
}

Green Green::operator+(const Green& A) {
  mat tval;
  tval = matrix + A.matrix;
  return Green(tval);
}

Green Green::operator-(const Green& A) {
  mat tval;
  tval = matrix - A.matrix;
  return Green(tval);
}

Green Green::operator*(const double& A) {
  mat tval;
  tval = matrix * A;
  return Green(tval);
}

Green Green::operator*(const std::complex<double>& A) {
  mat tval;
  tval = matrix * A;
  return Green(tval);
}

Green Green::operator/(const double& A) {
  mat tval;
  tval = matrix / A;
  return Green(tval);
}

Green Green::operator*(const Green& A) {
  mat tval;
  tval = matrix * A.matrix;
  return Green(tval);
}

