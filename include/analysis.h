#ifndef ANALYSIS_H
#define ANALYSIS_H
#include "../include/limits.h"
#include "../include/green.h"
#include "../include/data.h"
#include "../include/magtot.h"
#include "../include/dos.h"
#include "../include/hcond.h"
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

namespace ANA {
  void HCond(std::string data_folder) {
    std::ofstream ofile;
    ofile.open("HDATA", std::ios_base::app);
    Limits L;
    L.load(data_folder);
    HeatCond H(data_folder, L);
    std::vector<double> out = H.compute();
    ofile << L.magF << " " \
	  << L.tempInc << " " \
	  << out[0] << " " \
	  << out[1] << std::endl;
    ofile.close();
  }

  void Mag(std::string data_folder) {
    std::ofstream ofile;
    ofile.open("MAGDATA", std::ios_base::app);
    Limits L;
    L.load(data_folder);
    Magnetisation M(data_folder, L);
    ofile << L.magF << " " << L.tempInc << " " << M.compute() << std::endl;
    ofile.close();
  }

  void Dos(std::string data_folder) {
    int i;
    std::ofstream ofile;
    ofile.open("DOSDATA", std::ios_base::app);
    Limits L;
    L.load(data_folder);
    std::vector<double> ener = L.space(0);
    DOS D(data_folder, L);
    std::vector<double> data = D.compute(0);
    for (i=0; i<L.energyN; i++) {
      ofile << std::setprecision(10) << data[i] << " " << ener[i] << std::endl;
    }
    ofile.close();
  }

  void HandM(std::string data_folder) {
    std::ofstream ofile;
    ofile.open("TDATA", std::ios_base::app);
    Limits L;
    L.load(data_folder);
    HeatCond H(data_folder, L);
    Magnetisation M(data_folder, L);
    std::vector<double> out = H.compute();
    ofile << std::setprecision(10) << L.a1 << " " \
	  << L.a2 << " " \
	  << M.compute(1) << " "			\
	  << M.compute(2) << " "			\
	  << M.compute(3) << " "			\
	  << M.compute(4) << " "			\
	  << out[0] << " " \
	  << out[1] << std::endl;
    ofile.close();
  }

  void analysis(std::string data_folder) {
    //Mag(data_folder);
    //Dos(data_folder);
    HandM(data_folder);
  }
}
#endif
