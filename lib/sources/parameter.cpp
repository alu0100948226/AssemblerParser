#include "../headers/parameter.hpp"
Parameter::Parameter(): type_(""), size_(0){}
Parameter::Parameter(unsigned int size, std::string t): type_(t), size_(size){}
Parameter::~Parameter(){}

Parameter& Parameter::operator=(const Parameter& other){
  type_ = other.type();
  size_ = other.size();
  return *this;
}

std::string Parameter::type() const { return type_; }
unsigned int Parameter::size() const { return size_; }
