#ifndef __LABEL__
#define __LABEL__
#include <string>

class Label {
private:
  std::string label_;
  int         dir_;
public:
  Label(std::string labelName, int counter);
  ~Label();

  std::string label() const;
  int dir() const;
};

#endif
