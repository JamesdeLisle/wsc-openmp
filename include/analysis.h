#ifndef ANALYSIS_H
#define ANALYSIS_H
#include "../include/limits.h"
#include "../include/green.h"
#include "../include/data.h"
#include "../include/magtot.h"
#include "../include/dos.h"
#include <vector>
#include <string>
#include <fstream>

namespace ANA {
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
      ofile << data[i] << " " << ener[i] << std::endl;
    }
    ofile.close();
  }

  void analysis(std::string data_folder) {
    Mag(data_folder);
    //Dos(data_folder);
  }
}
#endif
