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

using namespace std;

namespace ANA {
  void HCond(string data_folder) {
    ofstream ofile;
    ofile.open("end/HDATA", ios_base::app);
    Limits L;
    L.load(data_folder);
    HeatCond H(data_folder, L);
    vector<double> out = H.compute();
    ofile << L.magF << " " \
	  << L.tempInc << " " \
	  << out[0] << " " \
	  << out[1] << endl;
    ofile.close();
  }

  void Mag(string data_folder) {
    ofstream ofile;
    ofile.open("end/MAGDATA", ios_base::app);
    Limits L;
    L.load(data_folder);
    Magnetisation M(data_folder, L);
    ofile << L.magF << " " << L.tempInc << " " << M.compute(3) << endl;
    ofile.close();
  }

  void Dos(string data_folder) {
    int i, spin;
    ofstream ofile;
    for (spin=0; spin<2; spin++) { 
      if (spin==1) {
	ofile.open("end/DOSDATAup", ios_base::app);
      }
      else {
	ofile.open("end/DOSDATAdn", ios_base::app);
      }
      Limits L;
      L.load(data_folder);
      vector<double> ener = L.space(0);
      DOS D(data_folder, L, spin);
      vector<double> data = D.compute(1);
      for (i=0; i<L.energyN; i++) {
	ofile << setprecision(10) << data[i] << " " << ener[i] << endl;
      }
      ofile.close();
    }
   }

  void HandM(string data_folder) {
    ofstream ofile;
    ofile.open("end/TDATA", ios_base::app);
    Limits L;
    L.load(data_folder);
    HeatCond H(data_folder, L);
    Magnetisation M(data_folder, L);
    vector<double> out = H.compute();
    double mout1 = M.compute(0); 
    double mout2 = M.compute(1); 
    ofile << setprecision(10)
	  << L.a1 << " "
	  << L.a2 << " " 
	  << mout1 << " " 
	  << mout2 << " "
	  << out[0] << " "
	  << out[1] << endl;
    ofile.close();
  }

  void MnD(string data_folder) {
    int i, spin;
    ofstream ofile;
    for (spin=0; spin<2; spin++) { 
      if (spin==1) {
	ofile.open("end/HDDATAup", ios_base::app);
      }
      else {
	ofile.open("end/HDDATAdn", ios_base::app);
      }
      Limits L;
      L.load(data_folder);
      vector<double> ener = L.space(0);
      DOS D(data_folder, L, spin);
      vector<double> data = D.compute(0);
      Magnetisation M(data_folder, L);
      ofile << setprecision(10)
	    << L.a1 << " "
	    << L.a2 << " "
	    << L.a3 << " "
	    << L.a4 << " # "
	    << M.compute(1)
	    << " # ";
      for (i=0; i<L.energyN; i++) {
	ofile << setprecision(10)
	      << data[i]
	      << " "
	      << ener[i]
	      <<  "|";
      }
      ofile << endl;
      ofile.close();
    }
  }

  void MnDK(string data_folder) {
    int i, spin;
    ofstream ofile;
    for (spin=0; spin<2; spin++) { 
      if (spin==1) {
	ofile.open("end/HDKDATAup", ios_base::app);
      }
      else {
	ofile.open("end/HDKDATAdn", ios_base::app);
      }
      Limits L;
      L.load(data_folder);
      vector<double> ener = L.space(0);
      DOSK D(data_folder, L, spin);
      vector<double> data = D.compute(0);
      Magnetisation M(data_folder, L);
      ofile << setprecision(10)
	    << L.a1
	    << " "
	    << L.a2
	    << " "
	    << L.a3
	    << " "
	    << L.a4
	    << " "
	    << "#"
	    << " "
	    << M.compute(1)
	    << " "
	    << "#"
	    << " ";
      for (i=0; i<L.energyN; i++) {
	ofile << setprecision(10) << data[i] << " " << ener[i] <<  "|";
      }
      ofile << endl;
      ofile.close();
    }
  }

  void TOTAL(string data_folder) {
    int i, spin;
    ofstream ofile;
    for (spin=0; spin<2; spin++) { 
      if (spin==1) {
	ofile.open("end/TOTALup", ios_base::app);
      }
      else {
	ofile.open("end/TOTALdn", ios_base::app);
      }
      Limits L;
      L.load(data_folder);
      DOSK DK(data_folder, L, spin);
      Magnetisation M(data_folder, L);
      DOS D(data_folder, L, spin);
      HeatCond H(data_folder, L);
      vector<double> heat = H.compute();
      vector<double> data00 = D.compute(0);
      vector<double> data01 = D.compute(1);
      vector<double> dataK = DK.compute(0);
      vector<double> dataK1 = DK.compute(1);
      vector<double> ener = L.space(0);
      ofile << setprecision(10)
	    << L.a1 << " "
	    << L.a2 << " "
	    << L.a3 << " "
	    << L.a4 << " # " 
	    << L.temp << " # "
	    << L.tempCrit << " # "
	    << L.tau << " # "
	    << L.fermVU << " # "
	    << L.fermVD << " # "
	    << L.tempInc << " # "
	    << L.magF << " # "
	    << M.compute(1) << " # "
	    << heat[spin] << " # ";
      for (i=0; i<L.energyN; i++) {
	ofile << setprecision(10)
	      << ener[i] << " "
	      << data00[i] <<  " | ";
      }
      ofile << " # ";
      for (i=0; i<L.energyN; i++) {
	ofile << setprecision(10)
	      << ener[i] << " "
	      << data01[i] <<  " | ";
      }
      ofile << " # ";
      for (i=0; i<L.energyN; i++) {
	ofile << setprecision(10)
	      << ener[i] << " "
	      << dataK[i] <<  " | ";
      }
      ofile << " # ";
      for (i=0; i<L.energyN; i++) {
	ofile << setprecision(10)
	      << ener[i] << " "
	      << dataK1[i] <<  " | ";
      }
      ofile << " # ";
      ofile << endl;
      ofile.close();
    }
  }
  
  void analysis(string data_folder) {
    std::cout << "Computing analysis..." << std::endl;
    //Mag(data_folder);
    //Dos(data_folder);
    //HandM(data_folder);
    //MnD(data_folder);
    //MnDK(data_folder);
    TOTAL(data_folder);
    std::cout << "Done." << std::endl;
  }
}


#endif
