#ifndef TIME_H
#define TIME_H
#include <string>
#include <ctime>

std::string getTime() {
  std::time_t now = time(0); 
  std::tm *ltm = localtime(&now);
  std::string year = std::to_string(1900 + ltm->tm_year);
  std::string month = std::to_string(1 + ltm->tm_mon);
  std::string day = std::to_string(ltm->tm_mday);
  std::string hour = std::to_string(ltm->tm_hour);
  std::string min = std::to_string(ltm->tm_min);
  std::string sec = std::to_string(ltm->tm_sec);
  return year + month + day + hour + min + sec;
}

class Timer
{
 private:
  std::clock_t start;
 public:
  Timer() : start() {start = std::clock();}
  void stop() {std::cout << ((std::clock() - start) / (double) CLOCKS_PER_SEC) /
      3600.0 << "mins" << std::endl;}
};  
#endif
