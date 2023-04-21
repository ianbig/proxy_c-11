#ifndef __requestAbstract_hpp__
#define __requestAbstract_hpp__

#include <string>
#include "header.hpp"

template <typename T>
class requestAbstract {
  private:
  Header<std::string, T> headers;
  public:
  virtual std::string getMessage() = 0;
  virtual int setHeader(std::string key, T val) = 0;
  virtual Header<string, T> getHeader() = 0;
  size_t getContentLength();
  virtual std::string getMethod() = 0;
};

#endif