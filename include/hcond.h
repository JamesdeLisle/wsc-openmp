#ifndef HCOND_H
#define HCOND_H
#include "data.h"
#include "limits.h"
#include <vector>


class HeatCond
{
 private:
  InData inDataU;
  InData inDataD;
  Limits lim;
 public:
  HeatCond(std::string data_folder, Limits _lim);
  std::vector<double> compute();
  double simpFac(int value, int max);
};

#endif
