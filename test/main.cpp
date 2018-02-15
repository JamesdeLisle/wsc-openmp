#include "../include/limits.h"
#include "../include/mainfunc.h"
#include "../include/time.h"
#include <iostream>
#include <complex>
#include <ctime>
#include <string>
#include <fstream>
#include <thread>
#include <vector>
#include <chrono>
#include <stdio.h>
#define PI 3.14159


int main(int argc, char * argv[]) {

   
  LimitsBox l;
  int max_order = 4;
  std::string folder = "data/";
  std::string time = getTime();
  MainFunc ENG(folder, time); 

  if (ENG.condAnal(argv[1])) {return 0;}

  l.spin = ENG.getSpin(argv[1]);
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
  l.alphaMax = 0.0;
  l.temp = 0.04;
  l.tempCrit = 0.1;
  l.a1 = 0.2;
  l.a2 = 0.6;
  l.a3 = 0.234;
  l.a4 = -0.123;
  l.tau = 0.01;
  l.fermVU = 1.0;
  l.fermVD = 0.75;
  l.tempInc = -0.03;
  l.magF = 0.3;
  l.start_time = time; 

  int disc = 25;
  Timer T = Timer();
  ENG.setThreads(22);
  ENG.run(l, max_order);
  T.stop();  

  return 0;
}
