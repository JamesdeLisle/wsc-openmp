#ifndef RUNGE_H
#define RUNGE_H
#include "../include/space.h"
#include "../include/green.h"
#include <vector>

template <class T>
class Runge
{
 private:
  RunVal runVal;
  Green fVal;
  T fClass;

 public:
  Runge(RunVal _runVal, T _fClass);
  std::vector<double> linspace(double min, double max, int disc);
  Green run();
};


template <class T> Runge<T>::Runge(RunVal _runVal, T _fClass) \
  : runVal(_runVal), fClass(_fClass) {
  fVal = fClass.bound();
}

template <class T> std::vector<double> Runge<T>::linspace(double min,
							  double max,
							  int disc) {
  int i;
  std::vector<double> rv;
  double step = (max - min) / disc;
  for (i=0; i<disc-1; i++) {
    rv.push_back(min + step * i);
  }
  rv.push_back(max);
  return rv;
}

template <class T> Green Runge<T>::run() {
  int i;
  std::vector<double> alph = this->linspace(runVal.getlim()->alphaMin,
					    runVal.getlim()->alphaMax,
					    runVal.getlim()->alphaN);
  std::vector<Green> kVals(4);
  for (i=0; i<runVal.getlim()->alphaN-1; i++) {
    fClass.setAlpha(alph.at(i));
    fClass.setiAlpha(i);
    kVals[0] = fClass.get(fVal);
    fClass.setAlpha(alph.at(i) + runVal.getlim()->alphaD / 2.0);
    kVals[1] = fClass.get(fVal + kVals[0] * (runVal.getlim()->alphaD / 2.0));
    kVals[2] = fClass.get(fVal + kVals[1] * (runVal.getlim()->alphaD / 2.0));
    fClass.setAlpha(alph.at(i) + runVal.getlim()->alphaD);
    kVals[3] = fClass.get(fVal + kVals[2] * runVal.getlim()->alphaD);
    fVal = fVal + (kVals[0] + (kVals[1] + kVals[2]) * 2.0 + kVals[3]) * \
      (runVal.getlim()->alphaD / 6.0);
  }
  return fVal;
}

#endif

