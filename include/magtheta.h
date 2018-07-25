#ifndef MAGTHETA_H
#define MAGTHETA_H
#include "data.h"
#include "limits.h"


class MagTheta
{
 private:
  InData inDataU;
  InData inDataD;
  Limits lim;
 public:
  MagTheta(std::string data_folder, Limits _lim);
  std::vector<double> compute(int order);
};

#endif
