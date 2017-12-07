#ifndef MAGTOT_H
#define MAGTOT_H
#include "data.h"
#include "limits.h"


class Magnetisation
{
 private:
  InData inDataU;
  InData inDataD;
  Limits lim;
 public:
  Magnetisation(std::string data_folder, Limits _lim);
  double compute(int order);
};

#endif
