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
  double r = 0.3;
  
  if (ENG.condAnal(argv[1], suffix)) {return 0;}
  int n_threads = std::atoi(argv[4]);

  l.spin = ENG.getSpin(argv[1]);
  l.energyN = 100;
  l.kPolarN = 50;
  l.kAzimuN = 100;
  l.alphaN = 300;
  l.energyMin = -1.0;
  l.energyMax = 1.0;
  l.kPolarMin = 1e-6;
  l.kPolarMax = PI;
  l.kAzimuMin = 1e-6;
  l.kAzimuMax = 2 * PI;
  l.alphaMin = -100.0;
  l.alphaMax = 0.0;
  l.temp = 0.02;
  l.tempCrit = 0.1;
  l.a1 = 1.0;
  l.a2 = l.a1 * r;
  l.a3 = r * l.a2;
  l.a4 = l.a1 * r;
  l.tau = 0.01;
  l.fermVU = 1.1;
  l.fermVD = 1.0;
  l.tempInc = 0.01 / l.alphaMax;
  l.magF = 0.3;
  l.start_time = time; 

  int disc = 20;
  vector<double> B = SPACE::linspace(0.01, 0.1, disc);
  
  Timer T = Timer();
  ENG.setThreads(n_threads);

  int i, j;
  for (i=0; i<disc; i++) {
    l.temp = B[i];
    //l.a2 = l.a1 * r;
    //l.a3 = r * l.a2;
    //l.a4 = l.a1 * r;
    ENG.run(l, max_order, suffix, flogp);
    //for (j=0; j<disc; j++) {
    //  l.temp = B[j];
      //}
  }
  T.stop();
  return 0;
}
