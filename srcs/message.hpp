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
  std::string raw;
  public:
  Message() = default;
  Message(const char * msg);
  virtual ~Message() = default;
  Message(HTTP_METHOD _method);
  Message(const Message & rhs) = default;
  Message(Message && rhs) = default;

  Message & operator=(const Message & rhs) = default;
  Message & operator=(Message && rhs) = default;

  const char * getMessage();
  void setHeader(std::string key, std::string val);
  Header<std::string, std::string> & getHeader();
  size_t getContentLength();
  HTTP_METHOD getMethod();
  void setBody(std::string _body);
  const char * getBody(); // easy for handling socket
  void setRaw(std::string raw);
  std::string getHost();
};

#endif