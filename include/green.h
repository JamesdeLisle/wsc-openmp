#ifndef GREEN_H
#define GREEN_H
#include <eigen3/Eigen/Dense>
#include <complex>
#include <iostream>

typedef Eigen::Matrix<std::complex<double>, 2, 2> mat;

class Green
{
 private:
  mat matrix;

 public:
  Green();
  Green(mat value) {matrix = value;}
  void set(int i, int j, std::complex<double> val) {matrix(i, j) = val;}
  void set(mat value) {matrix = value;}
  mat get() {return matrix;}
  std::complex<double> get(int i, int j) {return matrix(i, j);}
  mat getNorm() {return matrix * matrix;}
  std::complex<double> getZTrace(); 
  Green operator+(const Green& A);
  Green operator-(const Green& A);
  Green operator*(const double& A);
  Green operator*(const std::complex<double>& A);
  Green operator/(const double& A);
  Green operator*(const Green& A);
};

#endif
