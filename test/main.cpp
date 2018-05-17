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

using namespace std;

int main(int argc, char * argv[]) {

   
  LimitsBox l;
  int max_order = 4;
  string folder = "data/";
  string time = getTime();
  MainFunc ENG(folder, time);

  if (ENG.condAnal(argv[1])) {return 0;}
  
  int n_threads = std::atoi(argv[2]);

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
  l.alphaMin = -6.0;
  l.alphaMax = 0.0;
  l.temp = 0.06;
  l.tempCrit = 0.1;
  l.a1 = 0.5;
  l.a2 = 0.6;
  l.a3 = 0.7;
  l.a4 = 0.8;
  l.tau = 0.009;
  l.fermVU = 1.0;
  l.fermVD = 0.75;
  l.tempInc = 0.005;
  l.magF = 0.3;
  l.start_time = time; 

  int disc = 25;
  vector<double> A = SPACE::linspace(0.0, 1.0, disc);
  
  Timer T = Timer();
  ENG.setThreads(n_threads);
  ENG.run(l, max_order);
  /*
  int i, j;
  for (i=0; i<disc; i++) {
    l.a2 = A[i];
    for (j=0; j<disc; j++) {
      l.a2 = A[j];
      ENG.run(l, max_order);
    }
  }
  */
  T.stop();

  return 0;
}
