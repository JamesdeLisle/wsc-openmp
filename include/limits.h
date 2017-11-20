#ifndef LIMITS_H
#define LIMITS_H
#include <string>

struct LimitsBox
{
  bool spin;
  int energyN;
  int kPolarN;
  int kAzimuN;
  int alphaN;
  double energyMin;
  double energyMax;
  double kPolarMax; 
  double kPolarMin; 
  double kAzimuMax; 
  double kAzimuMin; 
  double alphaMax; 
  double alphaMin;
  double temp;
  double tempCrit;
  double tempInc;
  double a1;
  double a2;
  double a3;
  double a4;
  double magF;
  double tau;
  double fermVU;
  double fermVD;
  std::string start_time;
};

class Limits {
 public:
  bool spin;
  int energyN;
  int kPolarN;
  int kAzimuN;
  int tempN;
  int alphaN;
  double energyMin;
  double energyMax;
  double kPolarMax; 
  double kPolarMin; 
  double kAzimuMax; 
  double kAzimuMin; 
  double alphaMax; 
  double alphaMin;
  double alpha;
  double temp;
  double tempCrit;
  double tempInc;
  double a1;
  double a2;
  double a3;
  double a4;
  double magF;
  double tau;
  double fermVU;
  double fermVD;
  std::string start_time;
  double energyD;
  double kPolarD;
  double kAzimuD;
  double tempD;
  double alphaD;
  double gamma1;
  double gamma2;
  double fermV; 
  Limits(LimitsBox config);
  Limits() {}
  void save(std::string data_folder);
  void load(std::string data_folder);
};
  

#endif
