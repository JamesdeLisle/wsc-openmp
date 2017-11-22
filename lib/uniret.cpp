#include "../include/green.h"
#include "../include/space.h"
#include "../include/env.h"
#include "../include/uniret.h"
#include <complex>


UniRet::UniRet(RunVal _runVal) : runVal(_runVal) {
  runVal = _runVal;
}

Green UniRet::get() {
  Green rv;
  Environment E(runVal);
  rv = E.epsi() - E.hamR();
  rv = rv * (-1.0 / std::sqrt((runVal.getE() - E.getSigmaR()) *
			      (runVal.getE() - E.getSigmaR()) -
			      E.getDeltaR() * std::conj(E.getDeltaR())));
  return rv;
}
