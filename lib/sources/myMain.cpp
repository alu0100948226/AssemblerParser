#include <iostream>
#include "../headers/instr.hpp"
#include "../headers/label.hpp"
#include "../headers/parameter.hpp"
#include "../headers/assembler.hpp"
#include <cmath>
#include <cassert>
#include <string>
#include <vector>
#include <fstream>
//LIBS cassert
//LIBS cmath
//LIBS string

//TODO encode terminar con saltos
//TODO decodeInstruction.
//TODO Controlar errores en las etiquetas
//TODO

/**/
/*
std::vector<Instr> tableOfInstr;
std::vector<Label> tableOfLabel;
std::vector<std::string> program;
int counter = 0;
*/

/**/

/*
int extractInt(const std::string& tok){
  int result = 0;
  int inx = tok.size()-1;
  int ud = 1;
  while(tok[inx] > 47 && tok[inx] < 58){
    result += (tok[inx]-48)*ud;
    inx++;
    ud *= 10;
  }
  return result;
}


std::string binaryStr(int num, int n){
  assert(pow(2,n) > num);
  std::string final_n;
  final_n.resize(n);
  int res = num;
  int inx = n-1;
  while(res > 1){
    final_n[inx] = (char)res%2;
    res /= 2;
    inx--;
  }
  if (inx == 0)
    final_n[inx] == '1';
  else{
    for(int i = inx; i >= 0; i--){
      final_n[i] = '0';
    }
  }

  return final_n;
}



std::string encode(std::string token, Parameter par){
  std::string result;
  if(par.type() != Type::dir){
    int num = extractInt(token);
    result = binaryStr(num,par.size());
  }
  else {
    int i = 0;
    while(token != tableOfLabel[i].label())
      i++;
    if (i < tableOfLabel.size())
      result = binaryStr(tableOfLabel[i].dir(), par.size());
    else
      std::cout << "NO EXISTE LA ETIQUETA: " << token << '\n';
  }
  return result;
}



void encodeInstr(int i, std::string instr, std::string& prog){
  prog += tableOfInstr[i].encoding();
  int nprev = 0;
  for(unsigned inx = 0; inx < tableOfInstr[i].nPar() - 1; inx++){
    int n = instr.find_first_of(',', n);
    std::string token = instr.substr(nprev, n);
    prog += encode(token, tableOfInstr[i].par(inx));
    nprev = n+1;
  }
  std::string token = instr.substr(nprev, instr.size());
  prog += encode(token, tableOfInstr[i].par(tableOfInstr[i].nPar() - 1));

}

void decodeInstruction(std::string instr){
  bool isInstruction = false;
  std::string token;


  //Get name
  // Compare with table of instructions
  int n = instr.find_first_of(' ',0);
  token = instr.substr(0, n);
  //token = strtok();
  int i = 0;
  while(token != tableOfInstr[i].name() )
    i++;
  if ( i < tableOfInstr.size()){
    if(!tableOfInstr[i].sensitive()){
      encodeInstr(i, instr, program[counter]);
    }

    else {
      //TODO CASO DE OPERACIÓN DE SALTO
    }
    isInstruction = true;
    counter++;
  }

  else if ( token[0] == ':')
    tableOfLabel.push_back(Label(token, counter));

  else
    std::cout << "EL TOKEN: " << token << " NO ES UNA INSTRUCCIÓN O UNA ETIQUETA\n";
}

*/

int main( int argc, char * argv[]){
  std::cout << "\n\n-------------------------------BUILDING MACHINE---------------------------\n\n";
  Assembler g01(1024, "resources/instr_set.is");
  g01.printInstr(std::cout);

  std::cout << "\n\n-----------------------FINISHED BUILDING MACHINE---------------------------\n\n";
  //program.resize(1024);

  g01.buildProgram("resources/test");
  g01.printLabels(std::cout);
  g01.writeMachineCode();

}
