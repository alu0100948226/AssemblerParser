#ifndef __ASSEMBLER__
#define __ASSEMBLER__

#include <ifstream>

class Assembler {
private:
  std::vector<Instr>        tableOfInstr;
  std::vector<Label>        tableOfLabel;
  std::vector<std::string>  program;
  unsigned int              counter;
  unsigned int              memProgSize;

public:
  Assembler();  //TODO pasar parámetros
  ~Assembler();

  void buildProgram();
  void writeMachineCode(/*File*/);


private:
  int extractInt(const std::string& tok);
  std::string binaryStr(int num, int n);
  std::string encode(std::string token, Parameter par);
  void encodeInstr(int i, std::string instr, std::string& prog);

};


#endif /*__ASSEMBLER__*/
