#ifndef __messageInterface_hpp__
#define __messageInterface_hpp__

#include <string>

#include "header.hpp"
#include "httpInfo.hpp"


class messageAbstract {
  protected:
  Header<std::string, std::string> http_headers;
  HTTP_METHOD method;
  public:
  messageAbstract() = default;
  messageAbstract(HTTP_METHOD _method);
  messageAbstract(const messageAbstract & rhs) = default;
  messageAbstract(messageAbstract && rhs) = default;

  messageAbstract & operator=(const messageAbstract & rhs) = default;
  messageAbstract & operator=(messageAbstract && rhs) = default;

  std::string getMessage();
  void setHeader(std::string key, std::string val);
  Header<std::string, std::string> & getHeader();
  size_t getContentLength();
  HTTP_METHOD getMethod();
};

#endif