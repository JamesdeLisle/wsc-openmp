#ifndef ENV_H
#define ENV_H
#include "green.h"
#include "space.h"
#include <complex>

class Environment
{
 private:
  RunVal runVal;
  std::complex<double> deltaR;
  std::complex<double> deltaA;
  std::complex<double> deltaK;
  std::complex<double> sigmaR;
  std::complex<double> sigmaA;
  std::complex<double> sigmaK;
  double thermD;
  double thermDG;
 public:
  Environment(RunVal _runVal);
  Green hamR();
  Green hamA();
  Green hamK();
  Green hamKG();
  Green epsi();
  Green dzhamKG();
  std::complex<double> getSigmaR() {return sigmaR;}
  std::complex<double> getDeltaR() {return deltaR;}
  double getThermDG() {return thermDG;}
  double getThermD() {return thermD;}
};

#endif
