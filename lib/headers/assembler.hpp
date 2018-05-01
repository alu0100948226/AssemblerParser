#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cassert>
#include <cmath>

#include "instr.hpp"
#include "parameter.hpp"
#include "label.hpp"

#ifndef __ASSEMBLER__
#define __ASSEMBLER__

class Assembler {
private:
  std::vector<Instr>        tableOfInstr;
  std::vector<Label>        tableOfLabel;
  std::vector<int>          jumps;
  std::vector<std::string>  program;
  unsigned int              counter;
  unsigned int              memProgSize;

public:
  Assembler(unsigned int memprogsize, std::string intrsFormat );  //TODO pasar parámetros
  ~Assembler();

  void buildProgram(std::string inFileName);
  void writeMachineCode();

  std::ostream& printInstr(std::ostream& os);
  std::ostream& printLabels(std::ostream& os);


private:
  int extractInt(const std::string& tok);
  std::string binaryStr(int num, int n);
  std::string encode(std::string token, Parameter par);
  void encodeInstr(int i, std::string instr, std::string& prog);
  void decodeInstruction(std::string instr);

};
#endif /*__ASSEMBLER__*/
