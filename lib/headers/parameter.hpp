#ifndef __PARAMETER__
#define __PARAMETER__
#include <vector>
#include <string>


class Parameter {
private:
  std::string     type_;
  unsigned int    size_;

public:
  Parameter(unsigned int size, std::string t);
  ~Parameter();

  std::string type() const;
  unsigned int size() const;

};

#endif  /* __PARAMETER__ */
