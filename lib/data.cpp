#include "../include/data.h"
#include "../include/limits.h"
#include "../include/green.h"
#include "../include/name.h"
#include <fstream>
#include <complex>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <iomanip>

unsigned int split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
  unsigned int pos = txt.find(ch);
  unsigned int initialPos = 0;
  strs.clear();

  // Decompose statement
  int count = 0;
  while(count < 8) {
    strs.push_back(txt.substr(initialPos, pos - initialPos + 1));
    initialPos = pos + 1;
    pos = txt.find(ch, initialPos);
    count += 1;
  }
  // Add the last one
  strs.push_back( txt.substr( initialPos, std::min( pos, (unsigned int) txt.size() ) - initialPos + 1 ) );
  
  return strs.size();
}

Data::Data(Limits _lim, std::string _time,
	   int _order) : lim(_lim), name(Name(_lim)) {
  lim = _lim;
  name = Name(lim);
  time = _time;
  order = _order;
  int i, j;
  runData.resize(lim.energyN);
  for (i=0; i<lim.energyN; i++) {
    runData[i].resize(lim.kPolarN);
    for (j=0; j<lim.kPolarN; j++) {
      runData[i][j].resize(lim.kAzimuN, Green());
    }
  }
}

Data::Data(std::string data_folder, int _order) {
  std::ifstream infile;
  std::complex<double> values[4], I(0.0, 1.0);
  std::string LINE;
  std::vector<std::string> line;
  lim = Limits();
  lim.load(data_folder);
  name = Name();
  name.set(lim);
  order = _order;
  runData.resize(lim.energyN);
  int i, j, k, m;
  for (i=0; i<lim.energyN; i++) {
    runData[i].resize(lim.kPolarN);
    for (j=0; j<lim.kPolarN; j++) {
      runData[i][j].resize(lim.kPolarN, Green());
    }
  }
  for (i=0; i<lim.energyN; i++) {
    std::vector<std::vector<std::string> > lines;
    infile.open(data_folder + name.get(i, lim.start_time, order));
    std::cout << name.get(i, lim.start_time, order) << std::endl;
    for (std::string LINE; getline(infile, LINE);) {
      split(LINE, line, ' ');
      lines.push_back(line);
    }
    for (j=0; j<lim.kPolarN; j++) {
      for (k=0; k<lim.kAzimuN; k++) {
	m = j * lim.kAzimuN + k;
	values[0] = ::atof(lines[m][0].c_str()) + ::atof(lines[m][1].c_str()) * I;
	values[1] = ::atof(lines[m][2].c_str()) + ::atof(lines[m][3].c_str()) * I;
	values[2] = ::atof(lines[m][4].c_str()) + ::atof(lines[m][5].c_str()) * I;
	values[3] = ::atof(lines[m][6].c_str()) + ::atof(lines[m][7].c_str()) * I;
	runData[i][j][k].set(0, 0, values[0]);
	runData[i][j][k].set(0, 1, values[1]);
	runData[i][j][k].set(1, 0, values[2]);
	runData[i][j][k].set(1, 1, values[3]);
      }
    }
    infile.close();
  }
}

void Data::set(int i, int j, int k, Green value) {
  runData[i][j][k].set(value.get());
}

void Data::write(std::string _data_folder) {
  int i, j, k;
  Green G;
  std::ofstream outfile;
  for (i=0; i<lim.energyN; i++) {
    outfile.open(_data_folder + name.get(i, time, order));
    for (j=0; j<lim.kPolarN; j++) {
      for (k=0; k<lim.kAzimuN; k++) {
	G = runData[i][j][k];
	outfile << std::setprecision(10) << G.get(0, 0).real() << " ";
	outfile << std::setprecision(10) << G.get(0, 0).imag() << " ";
	outfile << std::setprecision(10) << G.get(0, 1).real() << " ";
	outfile << std::setprecision(10) << G.get(0, 1).imag() << " ";
	outfile << std::setprecision(10) << G.get(1, 0).real() << " ";
	outfile << std::setprecision(10) << G.get(1, 0).imag() << " ";
	outfile << std::setprecision(10) << G.get(1, 1).real() << " ";
	outfile << std::setprecision(10) << G.get(1, 1).imag() << std::endl;
      }
    }
    outfile.close();
  }
}

