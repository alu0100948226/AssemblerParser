#include "../headers/parameter.hpp"

Parameter::Parameter(unsigned int size, Type t): type_(t), size_(size){}
Parameter::~Parameter(){}

Type Parameter::type() const { return type_; }
unsigned int Parameter::size() const { return size_; }
