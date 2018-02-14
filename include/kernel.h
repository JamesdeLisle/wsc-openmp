#ifndef KERNEL_H
#define KERNEL_H
#include "data.h"
#include <iostream>
#include "../include/uniret.h"
#include "../include/unikel.h"
#include "../include/retard.h"
#include "../include/keldysh.h"
#include "../include/quantum.h"
#include "../include/quantumb.h"
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
  else if (order == 3) {
    Keldysh F(runVal,
	      inData->get(0, i, j, k),
	      inData->get(2, i, j, k),
	      inData->getDir(0, i, j, k));
    Runge<Keldysh> R(runVal, F);
    runData.set(i, j, k, R.run());
  }
  else if (order == 4) {
    Quantum F(runVal,
	      inData->get(0, i, j, k),
	      inData->getDir(0, i, j, k));
    Runge<Quantum> R(runVal, F);
    runData.set(i, j, k, R.run());
  }
  else if (order == 5) {
    Quantumb F(runVal,
	       inData->get(1, i, j, k),
	       inData->getDir(0, i, j, k),
	       inData->getDir(1, i, j, k));
    Runge<Quantumb> R(runVal, F);
    runData.set(i, j, k, R.run());
  }
}

#endif
