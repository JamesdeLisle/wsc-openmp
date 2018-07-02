#ifndef DOSK_H
#define DOSK_H
#include "data.h"
#include "limits.h"


class DOSK
{
 private:
  InData inDataU;
  InData inDataD;
  Limits lim;
 public:
  DOSK(std::string data_folder, Limits _lim, int spin);
  std::vector<double> compute(int order);
  double simpFac(int value, int max);
};

#endif
