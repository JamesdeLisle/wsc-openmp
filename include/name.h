#ifndef NAME_H
#define NAME_H
#include "../include/limits.h"
#include <string>
#include <vector>

typedef std::vector<std::string> stringvec;

class Name
{
 private:
  Limits lim;

 public:
  Name(Limits _lim);
  Name() {}
  void set(Limits _lim) {lim = _lim;};
  std::string get(int i, std::string time, int _order);
};

#endif
