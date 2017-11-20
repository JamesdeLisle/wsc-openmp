#ifndef DATA_H
#define DATA_H
#include "../include/green.h"
#include "../include/name.h"
#include <string>
#include <algorithm>
#include <eigen3/Eigen/Dense>

typedef std::vector<std::vector<std::vector<Green>>> GArray;

class Data
{
 private:
  Limits lim;
  GArray runData; 
  Name name;
  int order;
  std::string time;
  
 public:
  Data(Limits _lim, std::string _time, int _order);
  Data(std::string data_folder, int _order);
  void set(int i, int j, int k, Green value);
  mat get(int i, int j, int k) {return runData[i][j][k].get();}
  void write(std::string _data_folder);
};

#endif
