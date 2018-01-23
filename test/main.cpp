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
  l.energyN = 30;
  l.kPolarN = 5;
  l.kAzimuN = 10;
  l.alphaN = 10;
  l.energyMin = -1.0;
  l.energyMax = 1.0;
  l.kPolarMin = 1e-6;
  l.kPolarMax = PI;
  l.kAzimuMin = 1e-6;
  l.kAzimuMax = 2 * PI;
  l.alphaMin = -3.0;
  l.alphaMax = 0.0;
  l.temp = 0.02;
  l.tempCrit = 0.1;
  l.a1 = 0.32;
  l.a2 = 0.5;
  l.a3 = 0.234;
  l.a4 = -0.123;
  l.tau = 0.01;
  l.fermVU = 1.0;
  l.fermVD = 0.75;
  l.tempInc = 0.03;
  l.magF = 0.3;
  l.start_time = time; 

  std::vector<double> ANIS = SPACE::linspace(-0.25, 0.75, 100); 
  int i;

  //for (i=0; i<100; i++) {
  //  l.a1 = ANIS[i];
  ENG.run(l, max_order);
  //}
  return 0;
}
