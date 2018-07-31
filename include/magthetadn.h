#ifndef MAGTHETADN_H
#define MAGTHETADN_H
#include "data.h"
#include "limits.h"


class MagThetaDn
{
 private:
  InData inDataU;
  InData inDataD;
  Limits lim;
 public:
  MagThetaDn(std::string data_folder, Limits _lim);
  std::vector<double> compute(int order);
  double simpFac(int value, int max);
};

#endif
