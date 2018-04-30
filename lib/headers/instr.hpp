#ifndef __INSTR__
#define __INSTR__

//TODO Constructor de copia
//TODO Implementacion de push_parameter

#include <vector>
#include <string>
#include "parameter.hpp"

class Instr {
private:
  std::string               name_;
  std::string               encoding_;
  bool                      sensitive_;
  unsigned short int        nPar_;
  std::vector<Parameter>    par_;
public:
  Instr();
  ~Instr();

  std::string         name() const;
  std::string         encoding() const;
  bool                sensitive() const;
  unsigned short int  nPar() const;
  Parameter           par(unsigned int i);

  void                push_parameter(Parameter p);

};

#endif // __INSTR__
