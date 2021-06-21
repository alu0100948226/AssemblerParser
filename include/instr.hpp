#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include "parameter.hpp"

#ifndef __INSTR__
#define __INSTR__

//TODO Constructor de copia
//TODO Implementacion de push_parameter



class Instr {
private:
  std::string               name_;
  std::string               encoding_;
  bool                      sensitive_;
  unsigned short int        nPar_;
  std::vector<Parameter>    par_;
public:
  Instr();
  Instr(std::string instrName, std::string instrEncoding, bool sensitive,unsigned short int nParameters );
  ~Instr();

  Instr& operator=(const Instr& other);

  std::string         name() const;
  std::string         encoding() const;
  bool                sensitive() const;
  unsigned short int  nPar() const;
  Parameter           par(unsigned int i) const;

  void                push_parameter(Parameter p);

  std::ostream& print(std::ostream& os);

};

#endif // __INSTR__
