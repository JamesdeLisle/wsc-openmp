#ifndef MAINFUNC_H
#define MAINFUNC_H
#include "../include/schedule.h"
#include "../include/space.h"
#include "../include/limits.h"
#include <string>
#include <fstream>

class MainFunc
{
 private:
  std::string folder;
  std::string time;
  Schedule SCHED;
 public:
  MainFunc(std::string _folder, std::string _time);
  int getSpin(char * arg);
  bool condAnal(char * arg, std::string suffix);
  void run(LimitsBox l, int max_order, std::string suffix, std::ofstream * flog);
  void setThreads();
  void setThreads(int max);
};

#endif
