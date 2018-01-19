#ifndef DOS_H
#define DOS_H
#include "data.h"
#include "limits.h"


class DOS
{
 private:
  InData inData;
  Limits lim;
 public:
  DOS(std::string data_folder, Limits _lim, int spin);
  std::vector<double> compute(int order);
  double simpFac(int value, int max);
};

#endif
