#ifndef SCHEDULE_H
#define SCHEDULE_H
#include <fstream>
#include <chrono>
#include <thread>
#include <string>

class Schedule
{
 private:
  std::string folder;

 public:
  Schedule(std::string _data_folder);
  void sleep(int sec) {std::this_thread::sleep_for(std::chrono::seconds(sec));}
  void start(int spin);
  void stop(int spin);
  void pause(int spin);
  void clean(int spin);
};

#endif
