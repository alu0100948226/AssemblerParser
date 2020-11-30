#include "../headers/assembler.hpp"



Assembler::Assembler(unsigned int memprogsize, std::string intrsFormat, std::string outname): outfilename_(outname){
  std::vector<Parameter> pTypes;
  std::string junk;


  std::ifstream instrFile( intrsFormat.c_str(), std::ifstream::in);

  if(instrFile.is_open()){
    while(instrFile.peek() != '-'){

      std::string type;
      int size;
      instrFile >> type >> std::ws >> size >> std::ws;

      Parameter p(size,type);
      pTypes.push_back(p);
    }


    unsigned int nInstr;
    instrFile >> junk >> nInstr >> std::ws;

    tableOfInstr_.resize(nInstr);

    std::string instrName, sens, instrEncoding, type;
    bool sensitive;
    unsigned int nParameters;


    for(int i = 0; i < nInstr; i++){

      instrFile >> instrName >> std::ws >> sens >> std::ws >> nParameters >> std::ws >> instrEncoding >> std::ws;

      if (sens == "S")  sensitive = true;
      else              sensitive = false;
      Instr inst(instrName, instrEncoding, sensitive, nParameters );



      for(int count = 0; count < nParameters; count++){
        instrFile >> type >> std::ws;


        int inx = 0;
        while(inx < pTypes.size() && type != pTypes[inx].type())
          inx++;
        if(inx < pTypes.size())
          inst.push_parameter(pTypes[inx]);
      }

      tableOfInstr_[i] = inst;
    }

    memProgSize_ = memprogsize;
    program.resize(memProgSize_);
    instrFile.close();
  }
}

Assembler::~Assembler(){

}


void Assembler::buildProgram(std::string inFileName){
  counter_ = 0;
  std::cout << "BUILDING PROGRAM\n"; //DEBUG
  std::ifstream inFile(inFileName.c_str(), std::ifstream::in);
  std::string token;

  if(inFile.is_open()){
    while(!inFile.eof()){
      std::string instr;
      while(inFile.peek() != '\n'){
        std::string input;
        inFile >> input;
        instr += input + " ";
      }
      inFile >> std::ws;
      std::cout << instr << "\n"; //DEBUG
      decodeInstruction(instr);
      std::cout << "\n--------------------------INSTRUCTION DECODED--------------------------\n\n"; //DEBUG
    }



    for(int i = 0; i < jumps_.size(); i++){
      int n = program[jumps_[i]].find_first_of(' ',0);
      token = program[jumps_[i]].substr(0, n);
      std::string instrJump = program[jumps_[i]];

      std::cout << "J INSTR: " << token << '\n'; //DEBUG
      int inx = 0;
      while(inx < tableOfInstr_.size() && token != tableOfInstr_[inx].name() )
        inx++;
      if ( inx < tableOfInstr_.size()){
        program[jumps_[i]] = "";
        encodeInstr(inx, instrJump, program[jumps_[i]]);
      }
      else
        std::cout << "Error. No existe la instrucción: " << program[jumps_[i]] << '\n';
    }
  }

}

void Assembler::writeMachineCode(){ //TODO a fichero de salida
  std::cout << "Writing code to: " << outfilename_ << '\n';
  std::ofstream outfile;
  outfile.open(outfilename_);
  for(int i = 0; i <= counter_; i++){
    outfile << program[i] << '\n';
    std::cout << program[i] << '\n';
  }
  outfile.close();
}



int Assembler::extractInt(const std::string& tok){
  int result = 0;
  int inx = tok.size()-1;
  int ud = 1;
  while(tok[inx] > 47 && tok[inx] < 58){
    result += (tok[inx]-48)*ud;
    inx--;
    ud *= 10;
  }
  return result;
}


std::string Assembler::binaryStr(int num, int n){
  std::cout << n << '\n'; //DEBUG
  assert(pow(2,n) > num);
  std::string final_n;
  final_n.resize(n);
  int res = num;
  int inx = n-1;
  bool mark = false;
  while(res > 1){
    final_n[inx] = (res%2 == 0)? '0': '1';
    res /= 2;
    inx--;
  }

  if(inx >= 0 && num > 0){
    final_n[inx] = '1';
    inx--;
  }

  while(inx >= 0){
    final_n[inx] = '0';
    inx--;
  }

  return final_n;
}



std::string Assembler::encode(std::string token, Parameter par){
  std::cout << "ENCODING PARAMETER: " << par.type() << " TOKEN: " << token << '\n'; //DEBUG
  std::string result;
  if(par.type() != "DIR"){
    int num = extractInt(token);
    std::cout << "NUM: " << num << '\n';
    result = binaryStr(num,par.size());
    std::cout << "RESULT: " << result << '\n'; //DEBUG
  }
  else {
    int i = 0;
    std::cout << "ENCODING JUMP\n"; //DEBUG
    while(token != tableOfLabel_[i].label())
      i++;
    if (i < tableOfLabel_.size())
      result = binaryStr(tableOfLabel_[i].dir(), par.size());
    else
      std::cout << "NO EXISTE LA ETIQUETA: " << token << '\n';
  }
  return result;
}



void Assembler::encodeInstr(int i, std::string instr, std::string& prog){
  prog += tableOfInstr_[i].encoding();
  int nprev = instr.find_first_of(" ", 0);
  for(unsigned inx = 0; inx < tableOfInstr_[i].nPar() - 1; inx++){
    int n = instr.find_first_of(",", nprev);
    std::string token = instr.substr(nprev+1, n - nprev - 1);
    std::cout << "DELIMITADORES: " << nprev << ' ' << n << '\n'; //DEBUG
    prog += encode(token, tableOfInstr_[i].par(inx));
    nprev = n+1;
  }
  std::string token = instr.substr(nprev+1, instr.size() - nprev - 2);
  prog += encode(token, tableOfInstr_[i].par(tableOfInstr_[i].nPar() - 1));

}

void Assembler::decodeInstruction(std::string instr){
  std::cout << "INSTRUCTION: " << instr << '\n'; //DEBUG
  bool isInstruction = false;
  std::string token;


  //Get name
  // Compare with table of instructions
  int n = instr.find_first_of(" ",0);
  std::cout << "N: " << n << '\n'; //DEBUG
  token = instr.substr(0, n);
  //token = strtok();


  std::cout << "SEARCHING INSTRUCTION: " << token << '\n'; //DEBUG

  int i = 0;
  while(i < tableOfInstr_.size() && token != tableOfInstr_[i].name() )
    i++;
  std::cout << "FINISHED SEARCH\n"; //DEBUG
  if ( i < tableOfInstr_.size()){
    std::cout << "INSTRUCTION FOUND\n"; //DEBUG
    if(!tableOfInstr_[i].sensitive()){
      encodeInstr(i, instr, program[counter_]);
    }

    else {
      jumps_.push_back(counter_);
      program[counter_] = instr;
    }
    isInstruction = true;
    std::cout << "INCREASING COUNTER\n"; //DEBUG
    counter_++;
  }

  else if ( token[0] == ':'){
    tableOfLabel_.push_back(Label(token, counter_));
  }

  else
    std::cout << "EL TOKEN: " << token << " NO ES UNA INSTRUCCIÓN O UNA ETIQUETA\n";
}



std::ostream& Assembler::printInstr(std::ostream& os){
  for(int i = 0; i < tableOfInstr_.size(); i++)
    tableOfInstr_[i].print(os);
  os << '\n';
  return os;
}

std::ostream& Assembler::printLabels(std::ostream& os){
  os << "------------------------------LABELS------------------------------\n";
  for(int i = 0; i < tableOfLabel_.size(); i++){
    os << tableOfLabel_[i].label() << ' ' << tableOfLabel_[i].dir() << '\n';
  }
  return os;
}
