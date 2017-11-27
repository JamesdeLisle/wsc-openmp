#ifndef ANALYSIS_H
#define ANALYSIS_H
#include "../include/limits.h"
#include "../include/green.h"
#include "../include/data.h"
#include "../include/magtot.h"
#include <vector>
#include <string>
#include <fstream>

namespace ANA {
  void analysis(std::string data_folder) {
    std::ofstream ofile;
    ofile.open("MAGDATA", std::ios_base::app);
    Limits L;
    L.load(data_folder);
    Magnetisation M(data_folder, L);
    ofile << L.magF << " " << L.tempInc << " " << M.compute() << std::endl;
    ofile.close();
  }
}
#endif
