#include "label.hpp"

Label::Label(std::string labelName, int counter): label_(labelName), dir_(counter) {}

Label::~Label(){}


std::string Label::label() const { return label_; }

int Label::dir() const { return dir_; }
