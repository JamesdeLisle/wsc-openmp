#include "../include/env.h"
#include "../include/limits.h"
#include "../include/green.h"
#include "../include/space.h"
#include <complex>
#include <cmath>
#define PI 3.14159

Environment::Environment(RunVal _runVal) : runVal(_runVal) {
  std::complex<double> I(0.0, 1.0);
  runVal = _runVal;
  Limits * lim = runVal.getlim();
  runVal.comp();
  deltaR = 1.764 / (2.0 * PI);
  deltaR *= tanh(sqrt(lim->tempCrit / lim->temp - 1.0));
  deltaR *= sin(runVal.getXi());
  deltaR *= (lim->gamma1 * cos(runVal.getTheta()) \
    + I * lim->gamma2 * sin(runVal.getTheta()));
  deltaA = deltaR;
  deltaK = 0.0;

  sigmaR = -I * lim->tau;
  sigmaA = std::conj(sigmaR);
  sigmaK = sigmaA;
  thermD = tanh(runVal.getE() / (2 * lim->temp));
  thermDG = -runVal.getE() * runVal.getZ() * lim->tempInc;
  thermDG /= (2 * lim->temp * lim->temp *
	      cosh(runVal.getE() / (2 * lim->temp)) *
	      cosh(runVal.getE() / (2 * lim->temp)));
}
    
Green Environment::hamR() {
  Green rv;
  rv.set(0, 0, sigmaR);
  rv.set(1, 1, -sigmaR);
  rv.set(0, 1, -deltaR);
  rv.set(1, 0, std::conj(deltaR));
  return rv;
}

Green Environment::hamA() {
  Green rv;
  rv.set(0, 0, sigmaA);
  rv.set(1, 1, -sigmaA);
  rv.set(0, 1, -deltaA);
  rv.set(1, 0, std::conj(deltaA));
  return rv;
}

Green Environment::hamK() {
  Green rv;
  rv = (this->hamR() - this->hamA()) * thermD;
  return rv;
}

Green Environment::hamKG() {
  Green rv;
  rv = (this->hamR() - this->hamA()) * thermDG;
  return rv;
}
 
Green Environment::epsi() {
  Green rv;
  rv.set(0, 0, runVal.getE());
  rv.set(1, 1, -runVal.getE());
  rv.set(0, 1, 0.0);
  rv.set(1, 0, 0.0);
  return rv;
}
 
Green Environment::dzhamKG() {
  Limits * lim = runVal.getlim();
  Green rv, rv0;
  runVal.comp();
  rv0 = hamKG();
  runVal.setAlpha(runVal.getalpha() + lim->alphaD);
  runVal.comp();
  rv = rv + ((hamKG() - rv0) / lim->alphaD) * cos(runVal.getXi());
  runVal.setAlpha(runVal.getalpha() - lim->alphaD);
  runVal.setXi(runVal.getXi() + lim->kPolarD);
  runVal.comp();
  rv = rv - ((hamKG() - rv0) / (lim->kPolarD * lim->fermV)) * sin(runVal.getXi());
  runVal.setXi(runVal.getXi() - lim->kPolarD);
  return rv;
}
