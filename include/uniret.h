#ifndef UNI_H
#define UNI_H
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
