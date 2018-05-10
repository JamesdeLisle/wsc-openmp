#ifndef SPACE_H
#define SPACE_H
#include "../include/limits.h"
#include "../include/green.h"
#include "../include/data.h"
#include <vector>
#include <string>


class RunVal
{
 private:
  double E;
  double Xi;
  double Theta;
  double alpha;
  std::vector<int> index;
  Limits lim;
  double Z;
  int iAlpha;

 public:
  RunVal(double energy,
	 double kPolar,
	 double kAzimu,
	 std::vector<int> idx,
	 Limits L);
  double getE() {return E;}
  double getXi() {return Xi;}
  double getTheta() {return Theta;}
  double getalpha() {return alpha;}
  void setAlpha(double _alpha) {alpha = _alpha;}
  double getAlpha() {return alpha;}
  void setiAlpha(int _iAlpha) {iAlpha = _iAlpha;}
  void setXi(double _Xi) {Xi = _Xi;}
  double getZ() {return Z;}
  std::vector<int> getindex() {return index;}
  Limits * getlim() {return &lim;}
  void comp() {Z = -alpha * sin(Xi);}
};

class Space
{
 private:
  Limits lim;
  std::vector<double> energy;
  std::vector<double> kPolar;
  std::vector<double> kAzimu;
  std::string time;
  int order;
  Data runData; 
  
 public:
  Space();
  Space(Limits L, std::string _time, int _order);
  void run(std::string _data_folder);
  void progress(int i, int j);
  void test(std::string _data_folder);
  double simpFac(int value, int max);
};

namespace SPACE {
  std::vector<double> linspace(double min, double max, int disc);
}
#endif
