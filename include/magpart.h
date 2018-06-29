#ifndef MAGPART_H
#define MAGPART_H
#include "data.h"
#include "limits.h"


class MagnetisationPart
{
 private:
  InData inData;
  Limits lim;
 public:
  MagnetisationPart(std::string data_folder, Limits _lim, int spin);
  double compute(int order);
  double simpFac(int value, int max);
};

#endif
