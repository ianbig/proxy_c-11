#ifndef __messageInterface_hpp__
#define __messageInterface_hpp__

#include <string>

#include "header.hpp"
#include "httpInfo.hpp"


class messageInterface {
  public:
  virtual std::string getMessage() = 0;
  virtual void setHeader(std::string key, std::string val) = 0;
  virtual Header<std::string, std::string> & getHeader() = 0;
  virtual size_t getContentLength() = 0;
  virtual HTTP_METHOD getMethod() = 0;
};

#endif