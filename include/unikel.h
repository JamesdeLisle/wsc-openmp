#ifndef UNIKEL_H
#define UNIKEL_H
#include "../include/green.h"
#include "../include/space.h"
#include "../include/env.h"

typedef Eigen::Matrix<std::complex<double>, 2, 2> mat;

class UniKel
{
 private:
  RunVal runVal;
  mat ret0;
 public:
  UniKel(RunVal _runVal, mat _ret0);
  void setAlpha(double _alpha) {runVal.setAlpha(_alpha);}
  void setiAlpha(int i) {runVal.setiAlpha(i);}
  double getAlpha() {return runVal.getAlpha();}
  Green get(Green funcVal);
  Green bound();
};


#endif
