#ifndef __messageInterface_hpp__
#define __messageInterface_hpp__

#include <string>

#include "header.hpp"


class messageInterface {
  public:
  virtual std::string getMessage();
  virtual int setHeader(std::string key, std::string val);
  virtual Header<std::string, std::string> getHeader();
  virtual size_t getContentLength();
  virtual std::string getMethod();
};

#endif