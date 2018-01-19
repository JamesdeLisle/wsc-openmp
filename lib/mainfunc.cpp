#include "../include/mainfunc.h"
#include "../include/analysis.h"

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

void MainFunc::run(LimitsBox l, int max_order) {
  int order;
  SCHED.sleep(5);
  SCHED.start(l.spin);
  Limits L(l);
  L.save(folder);
  for (order=0; order<max_order; order++) {
    Space S(L, time, order);
    S.run(folder);
  }
  SCHED.stop(l.spin);
  SCHED.pause(l.spin);
  if (!l.spin) {ANA::analysis(folder);}
  SCHED.clean(l.spin);
}