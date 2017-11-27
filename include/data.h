#ifndef DATA_H
#define DATA_H
#include "../include/green.h"
#include "../include/name.h"
#include <string>
#include <algorithm>
#include <eigen3/Eigen/Dense>
#include <vector>
#include <map>

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
  Data(std::string data_folder, int spin, int _order);
  Data(std::string data_folder, int spin, int _order, Limits _lim);
  Data(Limits _lim);
  void set(int i, int j, int k, Green value);
  void set(int i, int j, int k, mat value);
  mat get(int i, int j, int k) {return runData[i][j][k].get();}
  void write(std::string _data_folder);
};

class InData
{
 private:
  std::vector<Data> store;
  std::vector<Data> deriv;
  Limits lim;
 public:
  InData(std::string data_folder, int spin, int order, Limits _lim);
  mat get(int index, int i, int j, int k) {return store[index].get(i, j, k);}
  mat getDir(int index, int i, int j, int k) {return deriv[index].get(i, j, k);}
  void dtheta(int order);
  void dpz(int order);
  std::vector<double> linspace(double min, double max, int disc);
};

#endif
