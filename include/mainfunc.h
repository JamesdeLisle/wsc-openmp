#ifndef MAINFUNC_H
#define MAINFUNC_H
#include "../include/schedule.h"
#include "../include/space.h"
#include "../include/limits.h"

class MainFunc
{
 private:
  std::string folder;
  std::string time;
  Schedule SCHED;
 public:
  MainFunc(std::string _folder, std::string _time);
  int getSpin(char * arg);
  bool condAnal(char * arg);
  void run(LimitsBox l, int max_order);
  void setThreads();
  void setThreads(int max);
};

#endif
