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
#include <typeinfo>

using namespace std;

unsigned int split(const string &txt,
		   vector<string> &strs,
		   char ch)
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
  strs.push_back( txt.substr( initialPos, min( pos, (unsigned int) txt.size() ) - initialPos + 1 ) );
  
  return strs.size();
}

void Data::build() {
  int i, j;
  runData.resize(lim.energyN);
  for (i=0; i<lim.energyN; i++) {
    runData[i].resize(lim.kPolarN);
    for (j=0; j<lim.kPolarN; j++) {
      runData[i][j].resize(lim.kAzimuN, Green());
    }
  }
}

void Data::write(string _data_folder) {
  int i, j, k;
  Green G;
  ofstream outfile;
  for (i=0; i<lim.energyN; i++) {
    outfile.open((const char *) (_data_folder +
				 name.get(lim.spin, i,
					  time, order)).c_str());
    for (j=0; j<lim.kPolarN; j++) {
      for (k=0; k<lim.kAzimuN; k++) {
	G = runData[i][j][k];
	outfile << setprecision(10) << G.get(0, 0).real() << " ";
	outfile << setprecision(10) << G.get(0, 0).imag() << " ";
	outfile << setprecision(10) << G.get(0, 1).real() << " ";
	outfile << setprecision(10) << G.get(0, 1).imag() << " ";
	outfile << setprecision(10) << G.get(1, 0).real() << " ";
	outfile << setprecision(10) << G.get(1, 0).imag() << " ";
	outfile << setprecision(10) << G.get(1, 1).real() << " ";
	outfile << setprecision(10) << G.get(1, 1).imag() << endl;
      }
    }
    outfile.close();
  }
}

void Data::read(string data_folder,
		int spin) {
  ifstream infile;
  complex<double> values[4], I(0.0, 1.0);
  string LINE;
  vector<string> line;

  int i, j, k, m;
  for (i=0; i<lim.energyN; i++) {
    vector<vector<string> > lines;
    infile.open((const char *) (data_folder +
				name.get(spin, i, lim.start_time, order)).c_str());
    if (infile.fail()) {
      cout << (data_folder + name.get(spin, i, lim.start_time, order)) << endl;
      cout << "FAILED TO LOAD DATA FILE" << endl;
    }
    for (string LINE; getline(infile, LINE);) {
      split(LINE, line, ' ');
      lines.push_back(line);
    }
    for (j=0; j<lim.kPolarN; j++) {
      for (k=0; k<lim.kAzimuN; k++) {
	m = j * (lim.kAzimuN - 1) + k;
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

Data::Data(Limits _lim) : lim(_lim) {
  lim = _lim;
  this->build();
}

Data::Data(Limits _lim,
	   string _time,
	   int _order) : lim(_lim), name(Name(_lim)) {
  lim = _lim;
  name = Name(lim);
  time = _time;
  order = _order;
  this->build();
}

Data::Data(string data_folder,
	   int spin,
	   int _order) {
  lim = Limits();
  lim.load(data_folder);
  name = Name();
  name.set(lim);
  order = _order;
  this->build();
  this->read(data_folder, spin);
}

Data::Data(string data_folder,
	   int spin,
	   int _order,
	   Limits _lim) : lim(_lim) {
  lim = _lim;
  name = Name();
  name.set(lim);
  order = _order;
  this->build();
  this->read(data_folder, spin);
}

void Data::set(int i,
	       int j,
	       int k,
	       Green value) {
  runData[i][j][k].set(value.get());
}

void Data::set(int i,
	       int j,
	       int k,
	       mat value) {
  runData[i][j][k].set(value);
}

void InData::dtheta(int order) {
  Data D(lim);
  int i, j, k;
  mat up, down, cval;
  for (i=0; i<lim.energyN; i++) {
    for (j=0; j<lim.kPolarN; j++) {
      for (k=0; k<lim.kAzimuN; k++) {
	if (k < lim.kAzimuN - 1) {
	  up = this->get(order, i, j, k + 1);
	}
	else {
	  up = this->get(order, i, j, 0);
	}
	down = this->get(order, i, j, k);
	cval = (up - down) / lim.kAzimuD;
	D.set(i, j, k, cval);
      }
    }
  }
  deriv.push_back(D);
}

vector<double> InData::linspace(double min,
				double max,
				int disc) {
  int i;
  vector<double> rv;
  double step = (max - min) / disc;
  for (i=0; i<disc-1; i++) {
    rv.push_back(min + step * i);
  }
  rv.push_back(max);
  return rv;
}

void InData::dpz(int order) {
  Data D(lim);
  int i, j, k;
  mat up, down, cval;
  vector<double> kPol = this->linspace(lim.kPolarMin,
					    lim.kPolarMax,
					    lim.kPolarN);
  for (i=0; i<lim.energyN; i++) {
    for (j=0; j<lim.kPolarN; j++) {
      for (k=0; k<lim.kAzimuN; k++) {
	if (j < lim.kPolarN - 1) {
	  up = this->get(order, i, j + 1, k);
	}
	else {
	  up = this->get(order, i, 0, k);
	}
	down = this->get(order, i, j, k);
	cval = -sin(kPol[j]) * (up - down) / (lim.kPolarN * lim.fermV);
	D.set(i, j, k, cval);
      }
    }
  }
  deriv.push_back(D);
}

InData::InData(string data_folder,
	       int spin,
	       int order,
	       Limits _lim) : lim(_lim) {
  lim = _lim;
  if (order == 0) {
    ;
  }
  else if (order == 1) {
    Data r0(data_folder, lim.spin, 0, lim);
    store.push_back(r0);
  }
  else if (order == 2) {
    Data r0(data_folder, lim.spin, 0, lim);
    store.push_back(r0);
    this->dtheta(0);
  }
  else if (order == 3) {
    Data r0(data_folder, lim.spin, 0, lim);
    Data k0(data_folder, lim.spin, 1, lim);
    Data r1(data_folder, lim.spin, 2, lim);
    store.push_back(r0);
    store.push_back(k0);
    store.push_back(r1);
    this->dtheta(1);
  }
  else if (order == 4) {
    Data r0(data_folder, lim.spin, 0, lim);
    store.push_back(r0);
    this->dpz(0);
  }
  else if (order == 5) {
    Data r0(data_folder, lim.spin, 0, lim);
    Data r1(data_folder, lim.spin, 2, lim);
    Data k2(data_folder, lim.spin, 4, lim);
    
    store.push_back(r0);
    store.push_back(r1);
    store.push_back(k2);
    this->dpz(1);
    this->dtheta(2);
  }
  else if (order == 10) {
    Data k0(data_folder, lim.spin, 1, lim);
    Data k1(data_folder, lim.spin, 3, lim);
    std::cout << "PROBLEM" << std::endl;
    Data k2(data_folder, lim.spin, 4, lim);
    Data k3(data_folder, lim.spin, 5, lim);
    store.push_back(k0);
    store.push_back(k1);
    store.push_back(k2);
    store.push_back(k3);
  }
  else if (order == 11) {
    Data r0(data_folder, lim.spin, 0, lim);
    Data r1(data_folder, lim.spin, 2, lim);
    store.push_back(r0);
    store.push_back(r1);
  }
  else if (order == 12) {
    Data k0(data_folder, lim.spin, 1, lim);
    store.push_back(k0);
    Data k1(data_folder, lim.spin, 3, lim);
    store.push_back(k1);
  }
}
