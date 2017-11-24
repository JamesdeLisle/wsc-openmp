#ifndef QUANTUMB_H
#define QUANTUMB_H
#include "../include/green.h"
#include "../include/space.h"
#include "../include/env.h"

typedef Eigen::Matrix<std::complex<double>, 2, 2> mat;

class Quantumb
{
 private:
  RunVal runVal;
  mat ret0;
  mat dpzret1;
 public:
  Quantumb(RunVal _runVal, mat _ret0, mat _dpzret1);
  void setAlpha(double _alpha) {runVal.setAlpha(_alpha);}
  void setiAlpha(int i) {runVal.setiAlpha(i);}
  double getAlpha() {return runVal.getAlpha();}
  Green get(Green funcVal);
  Green bound();
};


#endif
