#ifndef __message_hpp__
#define __message_hpp__

#include <string>

#include "header.hpp"
#include "httpInfo.hpp"


class Message {
  protected:
  Header<std::string, std::string> http_headers;
  HTTP_METHOD method;
  std::string body;
  public:
  Message() = default;
  virtual ~Message() = default;
  Message(HTTP_METHOD _method);
  Message(const Message & rhs) = default;
  Message(Message && rhs) = default;

  Message & operator=(const Message & rhs) = default;
  Message & operator=(Message && rhs) = default;

  std::string getMessage();
  void setHeader(std::string key, std::string val);
  Header<std::string, std::string> & getHeader();
  size_t getContentLength();
  HTTP_METHOD getMethod();
  void setBody(std::string _body);
  const char * getBody(); // easy for handling socket
  std::string getHost();
};

#endif