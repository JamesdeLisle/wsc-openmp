#ifndef KERNEL_H
#define KERNEL_H
#include "data.h"
#include <iostream>
#include "../include/uniret.h"
#include "../include/unikel.h"
#include "../include/retard.h"
#include "../include/runge.h"

void kernel(int i, int j, int k,
	    int order,
	    RunVal runVal,
	    InData * inData,
	    Data & runData) {
  if (order == 0) {
    UniRet F(runVal);
    runData.set(i, j, k, F.get());
  }
  else if (order == 1) {
    UniKel F(runVal, inData->get(0, i, j, k));
    Runge<UniKel> R(runVal, F);
    runData.set(i, j, k, R.run());
  }
  else if (order == 2) {
    Retarded F(runVal, inData->getDir(0, i, j, k));
    runData.set(i, j, k, F.get());
  }
}

#endif
