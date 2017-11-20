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
  l.kPolarMin = 0.0;
  l.kPolarMax = PI;
  l.kAzimuMin = 0.0;
  l.kAzimuMax = 2 * PI;
  l.alphaMin = -3.0;
  l.alphaMax = 0.0;
  l.temp = 0.01;
  l.tempCrit = 0.1;
  l.tempInc = 0.03;
  l.a1 = 0.3;
  l.a2 = 1.0;
  l.a3 = 1.0;
  l.a4 = 1.0;
  l.magF = 0.1;
  l.tau = 0.01;
  l.fermVU = 1.0;
  l.fermVD = 0.75;
  l.start_time = _start_time;
  Limits L(l);
  L.save(data_folder);
  L.load(data_folder);
  int order = 0;
  Space S(L, _start_time, order);
  S.run(data_folder);
  order = 1;
  S = Space(L, _start_time, order);
  S.run(data_folder);
  return 0;
}
