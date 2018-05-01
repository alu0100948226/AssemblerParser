#ifndef __PARAMETER__
#define __PARAMETER__
#include <vector>
#include <string>


class Parameter {
private:
  std::string     type_;
  unsigned int    size_;

public:
  Parameter();
  Parameter(unsigned int size, std::string t);
  ~Parameter();

  Parameter& operator=(const Parameter& other);
  std::string type() const;
  unsigned int size() const;

};

#endif  /* __PARAMETER__ */
