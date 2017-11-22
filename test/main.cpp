#include "../include/limits.h"
#include "../include/data.h"
#include "../include/pauli.h"
#include "../include/green.h"
#include "../include/space.h"
#include "../include/time.h"
#include <iostream>
#include <complex>
#include <ctime>
#include <string>
#define PI 3.14159

int main() {
  std::string data_folder = "data/";
  std::string _start_time = getTime();
  LimitsBox l;
  l.spin = 0;
  l.energyN = 100;
  l.kPolarN = 50;
  l.kAzimuN = 100;
  l.alphaN = 100;
  l.energyMin = -1.0;
  l.energyMax = 1.0;
  l.kPolarMin = 1e-6;
  l.kPolarMax = PI;
  l.kAzimuMin = 1e-6;
  l.kAzimuMax = 2 * PI;
  l.alphaMin = -3.0;
  l.alphaMax = -1e-6;
  l.temp = 0.01;
  l.tempCrit = 0.1;
  l.tempInc = 0.03;
  l.a1 = 0.332;
  l.a2 = 0.2314;
  l.a3 = -0.7654;
  l.a4 = 0.643;
  l.magF = 0.1;
  l.tau = 0.01;
  l.fermVU = 1.0;
  l.fermVD = 0.75;
  l.start_time = _start_time;
  Limits L(l);
  L.save(data_folder);
  L.load(data_folder);
  int order, max_order = 3;
  for (order=0; order<max_order; order++) {
    Space S(L, _start_time, order);
    S.run(data_folder);
  }
  return 0;
}
