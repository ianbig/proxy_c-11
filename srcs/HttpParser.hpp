#ifndef __htttp_parser_hpp__
#define __http_parser_hpp__

#define SPACE " "

#include <iostream>
#include <memory>
#include <exception>
#include "message.hpp"
#include "response.hpp"


class InvalidHTTPFormat: public std::exception {
  std::string msg;
  public:
  InvalidHTTPFormat(std::string msg);
};

using MessageUniquePtr = std::unique_ptr<Message>;
using ResponseUniquePtr = std::unique_ptr<Response>;

class HttpParser {
  private:
  MessageUniquePtr parseRequestStartLine(std::string http_msg);
  ResponseUniquePtr parserResponseStartLine(std::string http_msg);
  bool isResponse(std::string firstLine);
  bool isRequest(std::string method);
  int extractedCode(std::string firstLine);
  std::string extractMethod(std::string firstLine);
  bool isValidHttpFormat(std::string firstLine);
  void parseHeader(Message * msg, std::string http_msg);
  // void parseBody(MessageUniquePtr & msg, std::string http_msg);
  public:
  MessageUniquePtr parseRequest(std::string http_msg);
  ResponseUniquePtr parserResponse(std::string http_msg);
};

#endif