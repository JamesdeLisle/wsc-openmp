#ifndef ANALYSIS_H
#define ANALYSIS_H
#include "../include/limits.h"
#include "../include/green.h"
#include "../include/data.h"
#include "../include/magtot.h"
#include "../include/dos.h"
#include "../include/dosk.h"
#include "../include/hcond.h"
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

namespace ANA {
  void HCond(std::string data_folder) {
    std::ofstream ofile;
    ofile.open("end/HDATA", std::ios_base::app);
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
    ofile.open("end/MAGDATA", std::ios_base::app);
    Limits L;
    L.load(data_folder);
    Magnetisation M(data_folder, L);
    ofile << L.magF << " " << L.tempInc << " " << M.compute(4) << std::endl;
    ofile.close();
  }

  void Dos(std::string data_folder) {
    int i, spin;
    std::ofstream ofile;
    for (spin=0; spin<2; spin++) { 
      if (spin==1) {
	ofile.open("end/DOSDATAup", std::ios_base::app);
      }
      else {
	ofile.open("end/DOSDATAdn", std::ios_base::app);
      }
      Limits L;
      L.load(data_folder);
      std::vector<double> ener = L.space(0);
      DOS D(data_folder, L, spin);
      std::vector<double> data = D.compute(1);
      for (i=0; i<L.energyN; i++) {
	ofile << std::setprecision(10) << data[i] << " " << ener[i] << std::endl;
      }
      ofile.close();
    }
   }

  void HandM(std::string data_folder) {
    std::ofstream ofile;
    ofile.open("end/TDATA", std::ios_base::app);
    Limits L;
    L.load(data_folder);
    HeatCond H(data_folder, L);
    Magnetisation M(data_folder, L);
    std::vector<double> out = H.compute();
    double mout1 = M.compute(1); 
    double mout2 = M.compute(2); 
    ofile << std::setprecision(10) << L.a1 << " " \
	  << L.a2 << " " \
	  << mout1 << " "			\
	  << mout2 << " "			\
	  << out[0] << " " \
	  << out[1] << std::endl;
    ofile.close();
  }

  void MnD(std::string data_folder) {
    int i, spin;
    std::ofstream ofile;
    for (spin=0; spin<2; spin++) { 
      if (spin==1) {
	ofile.open("end/HDDATAup", std::ios_base::app);
      }
      else {
	ofile.open("end/HDDATAdn", std::ios_base::app);
      }
      Limits L;
      L.load(data_folder);
      std::vector<double> ener = L.space(0);
      DOS D(data_folder, L, spin);
      std::vector<double> data = D.compute(0);
      Magnetisation M(data_folder, L);
      ofile << std::setprecision(10) << L.a1 << " " << \
	L.a2 << " " << L.a3 << " " << L.a4 << " " << "#" << " ";
      ofile << M.compute(2) << " " << "#" << " ";
      for (i=0; i<L.energyN; i++) {
	ofile << std::setprecision(10) << data[i] << " " << ener[i] <<  "|";
      }
      ofile << std::endl;
      ofile.close();
    }
  }

  void MnDK(std::string data_folder) {
    int i, spin;
    std::ofstream ofile;
    for (spin=0; spin<2; spin++) { 
      if (spin==1) {
	ofile.open("end/HDKDATAup", std::ios_base::app);
      }
      else {
	ofile.open("end/HDKDATAdn", std::ios_base::app);
      }
      Limits L;
      L.load(data_folder);
      std::vector<double> ener = L.space(0);
      DOSK D(data_folder, L, spin);
      std::vector<double> data = D.compute(1);
      Magnetisation M(data_folder, L);
      ofile << std::setprecision(10) << L.a1 << " " << \
	L.a2 << " " << L.a3 << " " << L.a4 << " " << "#" << " ";
      ofile << M.compute(2) << " " << "#" << " ";
      for (i=0; i<L.energyN; i++) {
	ofile << std::setprecision(10) << data[i] << " " << ener[i] <<  "|";
      }
      ofile << std::endl;
      ofile.close();
    }
  }
  
  void analysis(std::string data_folder) {
    //Mag(data_folder);
    //Dos(data_folder);
    //HandM(data_folder);
    //MnD(data_folder);
    MnDK(data_folder);
  }
}


#endif
