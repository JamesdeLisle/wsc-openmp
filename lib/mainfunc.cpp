#include "../include/mainfunc.h"
#include "../include/analysis.h"
#include "omp.h"

MainFunc::MainFunc(std::string _folder, std::string _time) :
  folder(_folder), time(_time), SCHED(folder) {
  std::cout << folder << std::endl;}

int MainFunc::getSpin(char * arg) {
  if (std::strncmp(arg, "up", 2) == 0) {
    return 1;
  }
  else if (std::strncmp(arg, "dn", 2) == 0) { 
    return 0;
  }
  else {
    std::cout << "Input an invalid spin, you have." << std::endl;
    return 0;
  }
}

bool MainFunc::condAnal(char * arg, string suffix) {
  if (std::strncmp(arg, "an", 2) == 0) {
    ANA::analysis(folder, suffix);
    return 1;
  }
  else {
    return 0;
  }
}

void MainFunc::run(LimitsBox l, int max_order, string suffix, std::ofstream * flog) {
  int order;
  SCHED.sleep(5);
  SCHED.start(l.spin);
  Limits L(l);
  L.save(folder);
  for (order=0; order<max_order; order++) {
    Space S(L, time, order);
    S.run(folder, flog);
  }
  SCHED.stop(l.spin);
  SCHED.pause(l.spin);
  if (!l.spin) {ANA::analysis(folder, suffix);}
  SCHED.clean(l.spin);
}

void MainFunc::setThreads(int max) {
  omp_set_num_threads(max);
}

void MainFunc::setThreads() {
  int max_threads = omp_get_max_threads();
  omp_set_num_threads(max_threads - 2);
}
