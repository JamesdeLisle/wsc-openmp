#include "../include/name.h"
#include "../include/limits.h"
#include <string>
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <iomanip>

Name::Name(Limits _lim) : lim(_lim) {
  lim = _lim;
}



std::string Name::get(int i, std::string time, int _order) {
  std::ostringstream rv;
  rv << time;
  rv << "-";
  rv << _order;
  if (lim.spin) { 
    rv << "-up-";
  }
  else {
    rv << "-dn-";
  }
  rv << std::setfill('0') << std::setw(4) << i;
  return rv.str();
}
