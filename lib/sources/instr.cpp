#include "../headers/instr.hpp"

Instr::Instr() {}

Instr::~Instr() {}


std::string Instr::name() const { return name_; }

std::string Instr::encoding() const { return encoding_; }

bool Instr::sensitive() const { return sensitive_; }

unsigned short int  Instr::nPar() const { return par_.size(); }

Parameter Instr::par(unsigned int i){ return par_[i]; }
