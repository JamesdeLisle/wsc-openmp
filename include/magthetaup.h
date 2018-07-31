#ifndef MAGTHETAUP_H
#define MAGTHETAUP_H
#include "data.h"
#include "limits.h"


class MagThetaUp
{
 private:
  InData inDataU;
  InData inDataD;
  Limits lim;
 public:
  MagThetaUp(std::string data_folder, Limits _lim);
  std::vector<double> compute(int order);
  double simpFac(int value, int max);
};

#endif
