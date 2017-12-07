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
#include <time>
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

  //std::vector<double> MFIELD = SPACE::linspace(0.3, 0.0, 10); 
  //std::vector<double> TEMPIN = SPACE::linspace(0.03, 0.0, 10); 
  std::vector<double> ANIS = SPACE::linspace(0.5, 0.0, 50); 
  
  l.energyN = 75;
  l.kPolarN = 50;
  l.kAzimuN = 100;
  l.alphaN = 75;
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
  l.a1 = 0.0;
  l.a2 = 0.345;
  l.a3 = 0.234;
  l.a4 = -0.136;
  l.tau = 0.01;
  l.fermVU = 1.0;
  l.fermVD = 0.75;
  l.tempInc = 0.03;
  l.magF = 0.3;
  l.start_time = _start_time; 
  int i, j, order, max_order = 6;

  for (i=0; i<50; i++) {
    l.a1 = ANIS[i];
    for (j=0; j<50; j++) {
      const clock_t t0 = clock();
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
      l.a2 = ANIS[j];
      Limits L(l);
      L.save(data_folder);
      std::cout << L.a1 << " " << L.a2 << std::endl;
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
  
  /*
  for (i=0; i<50; i++) {
    l.a1 = ANIS[i];
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
    Limits L(l);
    L.save(data_folder);
    std::cout << L.a1 << " " << L.a2 << std::endl;
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
  */
  return 0;
}
