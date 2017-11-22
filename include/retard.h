#ifndef RETARD_H
#define RETARD_H
#include "green.h"
#include "space.h"

class Retarded
{
 private:
  RunVal runVal;
  mat dg0;
  
 public:
  Retarded(RunVal _runVal, mat dg0);
  Green get();
};

#endif
