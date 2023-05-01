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
  const char * what() const noexcept;
};

class HttpParser {
  private:
  Message parseRequestStartLine(std::string http_msg);
  Response parseResponseStartLine(std::string http_msg);
  bool isResponse(std::string firstLine);
  bool isRequest(std::string method);
  int extractedCode(std::string firstLine);
  std::string extractMethod(std::string firstLine);
  bool isValidHttpFormat(std::string firstLine);
  void parseHeader(Message & msg, std::string http_msg);
  std::string extractFieldInLine(const char * line);
  std::string extractValueInLine(const char * line);
  void parseBody(Message & msg, std::string http_msg);
  public:
  Message parseRequest(std::string http_msg);
  Response parseResponse(std::string http_msg);
};

#endif