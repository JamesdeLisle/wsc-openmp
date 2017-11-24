#ifndef MAGTOT_H
#define MAGTOT_H
#include "data.h"
#include "limits.h"


class Magnetisation
{
 private:
  InData inData;
  Limits lim;
 public:
  Magnetisation(std::string data_folder, Limits _lim);
  double compute();
};

#endif
