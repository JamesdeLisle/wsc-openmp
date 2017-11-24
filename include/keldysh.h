#ifndef KELDYSH_H
#define KELDYSH_H
#include "../include/green.h"
#include "../include/space.h"
#include "../include/env.h"

typedef Eigen::Matrix<std::complex<double>, 2, 2> mat;

class Keldysh
{
 private:
  RunVal runVal;
  mat ret0;
  mat ret1;
  mat dkel0;
 public:
  Keldysh(RunVal _runVal, mat _ret0, mat _ret1, mat _dkel0);
  void setAlpha(double _alpha) {runVal.setAlpha(_alpha);}
  void setiAlpha(int i) {runVal.setiAlpha(i);}
  double getAlpha() {return runVal.getAlpha();}
  Green get(Green funcVal);
  Green bound();
};


#endif
