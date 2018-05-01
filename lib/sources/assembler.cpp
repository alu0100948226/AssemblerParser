#include "../headers/assembler.hpp"



Assembler::Assembler(unsigned int memprogsize, std::string intrsFormat ){
  std::vector<Parameter> pTypes;
  std::string junk;


  std::ifstream instrFile( intrsFormat.c_str(), std::ifstream::in);

  if(instrFile.is_open()){
    while(instrFile.peek() != '-'){
      std::cout << "READING DATATYPES\n"; //DEBUG
      std::string type;
      int size;
      instrFile >> type >> std::ws >> size >> std::ws;
      std::cout << "Tipo: " << type << " SIZE: " << size << "\n"; //DEBUG
      Parameter p(size,type);
      pTypes.push_back(p);
    }

    std::cout << "READING NoI\n"; //DEBUG
    unsigned int nInstr;
    instrFile >> junk >> nInstr >> std::ws;
    std::cout << nInstr << '\n';

    tableOfInstr.resize(nInstr);

    std::string instrName, sens, instrEncoding, type;
    bool sensitive;
    unsigned int nParameters;

    std::cout << "READING INSTRUCTIONS\n"; //DEBUG
    for(int i = 0; i < nInstr; i++){
      std::cout << "\nREADING INSTRUCTIONS" << std::endl; //DEBUG
      instrFile >> instrName >> std::ws >> sens >> std::ws >> nParameters >> std::ws >> instrEncoding >> std::ws;

      if (sens == "S")  sensitive = true;
      else              sensitive = false;
      Instr inst(instrName, instrEncoding, sensitive, nParameters );

      std::cout << instrName << ' ' << sens << ' ' << nParameters << ' ' << instrEncoding << '\n'; //DEBUG

      for(int count = 0; count < nParameters; count++){
        instrFile >> type >> std::ws;

        std::cout << type << " IS PARAMETER: " << count << '\n'; //DEBUG
        int inx = 0;
        while(inx < pTypes.size() && type != pTypes[inx].type())
          inx++;
        if(inx < pTypes.size())
          inst.push_parameter(pTypes[inx]);
      }

      tableOfInstr[i] = inst;
    }

    memProgSize = memprogsize;
    program.resize(memProgSize);

  }
}

Assembler::~Assembler(){

}


void Assembler::buildProgram(std::string inFileName){
  std::ifstream inFile(inFileName.c_str(), std::ifstream::in);
  std::string token;

  if(inFile.is_open()){
    while(!inFile.eof()){
      std::string instr;
      while(inFile.peek() != '\n'){
        std::string input;
        inFile >> input;
        instr += input;
      }
      decodeInstruction(instr);
    }



    for(int i = 0; i < jumps.size(); i++){
      int n = program[jumps[i]].find_first_of(' ',0);
      token = program[jumps[i]].substr(0, n);

      int inx = 0;
      while(token != tableOfInstr[i].name() )
        inx++;
      if ( inx < tableOfInstr.size())
        encodeInstr(inx, program[jumps[i]], program[jumps[i]]);
      else
        std::cout << "Error. No existe la instrucción: " << program[jumps[i]] << '\n';
    }
  }

}

void Assembler::writeMachineCode(){ //TODO a fichero de salida
  for(int i = 0; i <= counter; i++){
    std::cout << program[i] << '\n';
  }
}



int Assembler::extractInt(const std::string& tok){
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


std::string Assembler::binaryStr(int num, int n){
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



std::string Assembler::encode(std::string token, Parameter par){
  std::string result;
  if(par.type() != "DIR"){
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



void Assembler::encodeInstr(int i, std::string instr, std::string& prog){
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

void Assembler::decodeInstruction(std::string instr){
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



std::ostream& Assembler::printInstr(std::ostream& os){
  for(int i = 0; i < tableOfInstr.size(); i++)
    tableOfInstr[i].print(os);
  os << '\n';
}
