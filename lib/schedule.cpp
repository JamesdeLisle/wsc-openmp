#include "../include/schedule.h"
#include <thread>
#include <chrono>
#include <fstream>
#include <iostream>

Schedule::Schedule(std::string _data_folder) : folder(_data_folder) {}

void Schedule::start(int spin) {
    std::ofstream TRACKU;
    TRACKU.open((const char *) (folder + "TRACKU").c_str());
    TRACKU.close();
    std::ofstream TRACKD;
    TRACKD.open((const char *) (folder + "TRACKD").c_str());
    TRACKD.close();
}

void Schedule::stop(int spin) {
  if (spin) {
    std::remove((const char *) (folder + "TRACKU").c_str());
  }
}

void Schedule::pause(int spin) {
  if (spin) {
    while (std::ifstream((const char *) (folder + "TRACKD").c_str())) {
      std::this_thread::sleep_for(std::chrono::seconds(2));
    }
  }
  else {
    while (std::ifstream((const char *) (folder + "TRACKU").c_str())) {
      std::this_thread::sleep_for(std::chrono::seconds(2));
    }
  }
}

void Schedule::clean(int spin) {
  if (spin) {}
  else {
    std::remove((const char *) (folder + "TRACKD").c_str());
  }
}
