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
#include <unistd.h>

enum args {nlines, instrSet, outfile, inProgram };

void help() {
  std::cout << "Something went wrong. Be sure you executed the program with all the arguments correctly:\n";
  std::cout << " - n: Set the max number of lines of the program file\n";
  std::cout << " - i: Set the instruction Set filename\n";
  std::cout << " - o: Set the output filename\n";
  std::cout << " - p: Set the input assembler program file\n\n";
  std::cout << "Usage: bin/sim 1024 resources/instr_set.is outfile resources/test\n";
}

int main( int argc, char * argv[]){
  
  std::vector<bool> argFlags;
  argFlags.resize(4);
  int linesOfCode = -1;
  std::string instructionsFile, outputFile, programFile;

  char option;

  std::cout << "Starting arguments parsing\n";
  while ((option = getopt(argc, argv, "n:i:o:p:")) != -1){
    std::cout << "Arg: " << option << '\n';
    std::cout << "optarg: " << optarg <<'\n';
    switch(option){
      case 'n':
        std::cout << "nLines called\n";
        argFlags[nlines] = true;
        std::cout << "Flag raised\n";
        linesOfCode = std::stoi(optarg);
        std::cout << "arg set\n";
        break;

      case 'i':
        argFlags[instrSet] = true;
        instructionsFile = optarg;
        break;

      case 'o':
        argFlags[outfile] = true;
        outputFile = optarg;
        break;

      case 'p':
        argFlags[inProgram] = true;
        programFile = optarg;
        break;

      default:
        help();
        abort();
    }
  }

  for(auto arg: argFlags){
    if(arg == false){
      help();
      abort();
    }
  }

  std::cout << "\n\n-------------------------------BUILDING MACHINE---------------------------\n\n";
  Assembler g01( linesOfCode, instructionsFile, outputFile);
  g01.printInstr(std::cout);

  std::cout << "\n\n-----------------------FINISHED BUILDING MACHINE---------------------------\n\n";
  //program.resize(1024);

  g01.buildProgram(programFile);
  g01.printLabels(std::cout);
  g01.writeMachineCode();

}
