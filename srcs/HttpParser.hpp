#ifndef __htttp_parser_hpp__
#define __http_parser_hpp__

#define SPACE " "

#include <exception>
#include "message.hpp"

class InvalidStartLine: public std::exception {

};

class InvalidHeader: public std::exception {

};

class InvalidHTTPFormat: public std::exception {

};

class HttpParser {
  private:
  void parseStartLine(Message & msg, std::string http_msg);
  void parseHeader(Message & msg, std::string http_msg);
  void parseBody(Message & msg, std::string http_msg);
  public:
  Message parse(std::string http_msg);
};

#endif