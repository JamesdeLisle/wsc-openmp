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
#include <fstream>
#define PI 3.14159

using namespace std;

int main(int argc, char * argv[]) {


  LimitsBox l;
  ofstream flog;
  int max_order = 4;
  string folder(argv[2]);
  string suffix(argv[3]);
  string time = getTime();
  string logname = "end/log" + suffix + (string) argv[1]; 
  remove((const char *) logname.c_str());
  flog.open((const char *) logname.c_str());
  ofstream * flogp = &flog;
  MainFunc ENG(folder, time);
  
  if (ENG.condAnal(argv[1], suffix)) {return 0;}
  int n_threads = std::atoi(argv[4]);

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
  l.temp = 0.02;
  l.tempCrit = 0.1;
  l.a1 = 0.5;
  l.a2 = 0.6;
  l.a3 = 0.0;
  l.a4 = 0.2;
  l.tau = 0.01;
  l.fermVU = 1.1;
  l.fermVD = 1.0;
  l.tempInc = 0.015;
  l.magF = 0.3;
  l.start_time = time; 

  int disc = 10;
  vector<double> A = SPACE::linspace(-1.0, 1.0, disc) ;
  vector<double> B = SPACE::linspace(0.0, 0.7, disc);
  
  Timer T = Timer();
  ENG.setThreads(n_threads);
  
  int i, j;
  for (i=0; i<disc; i++) {
    l.a3 = B[i];
    for (j=0; j<disc; j++) {
      l.a1 = A[j];
      l.a2 = A[j];
      ENG.run(l, max_order, suffix, flogp);
    }
  }
  T.stop();
  return 0;
}
