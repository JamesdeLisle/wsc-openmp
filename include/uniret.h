#ifndef UNIRET_H
#define UNIRET_H
#include "green.h"
#include "space.h"

class UniRet
{
 private:
  Green value;
  RunVal runVal;

 public:
  UniRet(RunVal _runVal);
  Green get();
};

#endif
