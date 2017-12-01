#include "../include/limits.h"
#include "../include/data.h"
#include "../include/pauli.h"
#include "../include/green.h"
#include "../include/space.h"
#include "../include/time.h"
#include "../include/analysis.h"
#include <iostream>
#include <complex>
#include <ctime>
#include <string>
#include <fstream>
#include <thread>
#include <vector>
#include <chrono>
#include <stdio.h>
#define PI 3.14159


int main(int argc, char * argv[]) {
  
  std::string data_folder = "data/";
  std::string _start_time = getTime();
  
  LimitsBox l;
  if (std::strncmp(argv[1], "up", 2) == 0) {
    l.spin = 1;
  }
  else if (std::strncmp(argv[1], "dn", 2) == 0) { 
    l.spin = 0;
  }
  else {
    std::cout << "Input an invalid spin, you have." << std::endl;
    return 0;
  }

  std::ofstream TRACKU;
  std::ofstream TRACKD;
  std::ifstream CHECK;

  std::vector<double> MFIELD = SPACE::linspace(0.3, 0.0, 10); 
  std::vector<double> TEMPIN = SPACE::linspace(0.03, 0.0, 10); 
  
  l.energyN = 200;
  l.kPolarN = 50;
  l.kAzimuN = 100;
  l.alphaN = 100;
  l.energyMin = -1.0;
  l.energyMax = 1.0;
  l.kPolarMin = 1e-6;
  l.kPolarMax = PI;
  l.kAzimuMin = 1e-6;
  l.kAzimuMax = 2 * PI;
  l.alphaMin = -3.0;
  l.alphaMax = 0.0;
  l.temp = 0.02;
  l.tempCrit = 0.1;
  l.a1 = 0.135;
  l.a2 = 0.22;
  l.a3 = 0.48;
  l.a4 = -0.242;
  l.tau = 0.01;
  l.fermVU = 1.0;
  l.fermVD = 0.75;
  l.tempInc = 0.03;
  l.magF = 0.3;
  l.start_time = _start_time; 
  int i, j, order, max_order = 6;
  for (i=0; i<10; i++) {
    l.tempInc = TEMPIN[i];
    for (j=0; j<10; j++) {
      if (l.spin) {
	std::this_thread::sleep_for(std::chrono::seconds(5));
	TRACKU.open((const char *) (data_folder + "TRACKU").c_str());
	TRACKU.close();
      }
      else {
	std::this_thread::sleep_for(std::chrono::seconds(5));
	TRACKD.open((const char *) (data_folder + "TRACKD").c_str());
	TRACKD.close();
      }
      l.magF = MFIELD[j];
      Limits L(l);
      L.save(data_folder);
      std::cout << L.magF << " " << L.tempInc << std::endl;
      for (order=0; order<max_order; order++) {
	Space S(L, _start_time, order);
	S.run(data_folder);
      }
      if (l.spin) {
	std::remove("data/TRACKU");
	while (std::ifstream(data_folder + "TRACKD")) {
	  std::this_thread::sleep_for(std::chrono::seconds(2));
	}
      }
      else {	
        while (std::ifstream(data_folder + "TRACKU")) {
	  std::this_thread::sleep_for(std::chrono::seconds(2));
	}
	ANA::analysis(data_folder);
	std::remove("data/TRACKD");
      }
    }
  }
  return 0;
}
