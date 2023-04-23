#ifndef __htttp_parser_hpp__
#define __http_parser_hpp__

#define SPACE " "

#include <iostream>
#include <memory>
#include <exception>
#include "message.hpp"
#include "response.hpp"


const char * getNextAlphabetInStr(const char * str);

class InvalidHTTPFormat: public std::exception {
  std::string msg;
  public:
  InvalidHTTPFormat(std::string msg);
};

using MessagePtr = std::shared_ptr<Message>;
using ResponsePtr = std::shared_ptr<Response>;

class HttpParser {
  private:
  MessagePtr parseRequestStartLine(std::string http_msg);
  ResponsePtr parseResponseStartLine(std::string http_msg);
  bool isResponse(std::string firstLine);
  bool isRequest(std::string method);
  int extractedCode(std::string firstLine);
  std::string extractMethod(std::string firstLine);
  bool isValidHttpFormat(std::string firstLine);
  void parseHeader(MessagePtr msg, std::string http_msg);
  std::string extractHeader(std::string msg);
  // void parseBody(MessageUniquePtr & msg, std::string http_msg);
  public:
  MessagePtr parseRequest(std::string http_msg);
  ResponsePtr parseResponse(std::string http_msg);
};

#endif