#include "../headers/instr.hpp"

Instr::Instr() {}

Instr::Instr(std::string instrName, std::string instrEncoding, bool sensitive,unsigned short int nParameters ){
  name_ = instrName;
  encoding_ = instrEncoding;
  sensitive_ = sensitive;
  nPar_ = 0;
}

Instr::~Instr() {}


Instr& Instr::operator=(const Instr& other){
  name_     = other.name();
  encoding_ = other.encoding();
  sensitive_ = other.sensitive();
  nPar_ = other.nPar();
  par_.resize(nPar_);
  for(int i = 0; i < nPar_; i++){
    par_[i] = other.par(i);
  }
  return *this;
}

std::string Instr::name() const { return name_; }

std::string Instr::encoding() const { return encoding_; }

bool Instr::sensitive() const { return sensitive_; }

unsigned short int  Instr::nPar() const { return par_.size(); }

Parameter Instr::par(unsigned int i) const { return par_[i]; }

void Instr::push_parameter(Parameter p){
  par_.push_back(p);
  nPar_++;
}

std::ostream& Instr::print(std::ostream& os){
  os << std::setw(8) << name_;
  os << std::setw(4) << ((sensitive_)? " S ": " NS ");
  os << std::setw(20) << encoding_;
  os << ' ' << std::setw(4) << nPar_;
  for(int i = 0; i < nPar_; i++)
    os << ' ' << std::setw(6) << par_[i].type();
  os << '\n';
  return os;
}
