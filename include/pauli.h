#ifndef PAULI_H
#define PAULI_H
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/StdVector>
#include <complex>
#include <vector>

typedef Eigen::Matrix<std::complex<double>, 2, 2> mat;

class Pauli
{
 private:
  std::vector<mat, Eigen::aligned_allocator<mat>> values;

 public:
  Pauli();
  mat get(int val) {return values[val];}
};

#endif
