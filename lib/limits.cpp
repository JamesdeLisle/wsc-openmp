#include "../include/limits.h"
#include <exception>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h>

Limits::Limits(LimitsBox config)
{
  spin = config.spin;
  energyN = config.energyN;
  kPolarN = config.kPolarN;
  kAzimuN = config.kAzimuN;
  alphaN = config.alphaN;
  energyMin = config.energyMin;
  energyMax = config.energyMax;
  kPolarMax = config.kPolarMax;
  kPolarMin = config.kPolarMin;
  kAzimuMax = config.kAzimuMax;
  kAzimuMin = config.kAzimuMin;
  alphaMax = config.alphaMax;
  alphaMin = config.alphaMin;
  alpha = alphaMin;
  temp = config.temp;
  tempCrit = config.tempCrit;
  tempInc = config.tempInc;
  a1 = config.a1;
  a2 = config.a2;
  a3 = config.a3;
  a4 = config.a4;
  magF = config.magF;
  tau = config.tau;
  fermVU = config.fermVU;
  fermVD = config.fermVD;
  start_time = config.start_time;
  energyD = (energyMax - energyMin) / energyN;
  kPolarD = (kPolarMin - kPolarMax) / kPolarN;
  kAzimuD = (kAzimuMin - kAzimuMax) / kAzimuN;
  alphaD = (alphaMin - alphaMax) / alphaN;
  if (spin) {
    gamma1 = a1 - a4;
    gamma2 = a2 + a3;
    fermV = fermVU;
  }
  else {
    gamma1 = -a1 - a4;
    gamma2 = -a2 + a3;
    fermV = fermVD;
  }
}

void Limits::save(std::string data_folder) {
  std::ostringstream out;
  std::ofstream outfile;
  std::string file_name = "CONFIG";
  out << spin << std::endl;
  out << energyN << std::endl;
  out << kPolarN << std::endl;
  out << kAzimuN << std::endl;
  out << alphaN << std::endl;
  out << energyMin << std::endl;
  out << energyMax << std::endl;
  out << kPolarMax << std::endl; 
  out << kPolarMin << std::endl; 
  out << kAzimuMax << std::endl; 
  out << kAzimuMin << std::endl; 
  out << alphaMax << std::endl; 
  out << alphaMin << std::endl;
  out << temp << std::endl;
  out << tempCrit << std::endl;
  out << tempInc << std::endl;
  out << a1 << std::endl;
  out << a2 << std::endl;
  out << a3 << std::endl;
  out << a4 << std::endl;
  out << magF << std::endl;
  out << tau << std::endl;
  out << fermVU << std::endl;
  out << fermVD << std::endl;
  out << start_time;
  outfile.open(data_folder + file_name);
  outfile << out.str();
  outfile.close();
}

void Limits::load(std::string data_folder) {
  std::ifstream infile;
  std::string file_name = "CONFIG";
  char out[100];
  std::vector<std::string> values;
  infile.open(data_folder + file_name);
  while (!infile.eof()) {
    infile >> out;
    std::string str(out);
    values.push_back(str);
  }
  spin = ::atoi(values[0].c_str());
  energyN = ::atoi(values[1].c_str());
  kPolarN = ::atoi(values[2].c_str());
  kAzimuN = ::atoi(values[3].c_str());
  alphaN = ::atoi(values[4].c_str());
  energyMin = ::atof(values[5].c_str());
  energyMax = ::atof(values[6].c_str());
  kPolarMax = ::atof(values[7].c_str());
  kPolarMin = ::atof(values[8].c_str());
  kAzimuMax = ::atof(values[9].c_str());
  kAzimuMin = ::atof(values[10].c_str());
  alphaMax = ::atof(values[11].c_str());
  alphaMin = ::atof(values[12].c_str());
  alpha = alphaMin;
  temp = ::atof(values[13].c_str());
  tempCrit = ::atof(values[14].c_str());
  tempInc = ::atof(values[15].c_str());
  a1 = ::atof(values[16].c_str());
  a2 = ::atof(values[17].c_str());
  a3 = ::atof(values[18].c_str());
  a4 = ::atof(values[19].c_str());
  magF = ::atof(values[20].c_str());
  tau = ::atof(values[21].c_str());
  fermVU = ::atof(values[22].c_str());
  fermVD = ::atof(values[23].c_str());
  start_time = values[24].c_str();
  energyD = (energyMax - energyMin) / energyN;
  kPolarD = (kPolarMin - kPolarMax) / kPolarN;
  kAzimuD = (kAzimuMin - kAzimuMax) / kAzimuN;
  alphaD = (alphaMin - alphaMax) / alphaN;
  if (spin) {
    gamma1 = a1 - a4;
    gamma2 = a2 + a3;
    fermV = fermVU;
  }
  else {
    gamma1 = -a1 - a4;
    gamma2 = -a2 + a3;
    fermV = fermVD;
  }
}

std::vector<double> Limits::space(int axis) {
  double min, max;
  int i, disc;
  std::vector<double> rv;
  if (axis == 0) {
    min = energyMin;
    max = energyMax;
    disc = energyN;
  }
  else if (axis == 1) {
    min = kPolarMin;
    max = kPolarMax;
    disc = kPolarN;
  }
  else if (axis == 2) {
    min = kAzimuMin;
    max = kAzimuMax;
    disc = kAzimuN;
  }
  double step = (max - min) / disc;
  for (i=0; i<disc-1; i++) {
    rv.push_back(min + step * i);
  }
  rv.push_back(max);
  return rv;
}
