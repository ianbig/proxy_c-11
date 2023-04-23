#include "HttpParser.hpp"

Message HttpParser::parse(std::string http_msg) {
  Message toRet;
  try {
    this->parseStartLine(toRet, http_msg);
    this->parseHeader(toRet, http_msg);
    this->parseBody(toRet, http_msg);
  } catch(InvalidStartLine & e) {
    throw InvalidHTTPFormat();
  } catch(InvalidHeader & e) {

  }

  return toRet;
}

void HttpParser::parseStartLine(Message & msg, std::string http_msg) {
  size_t end = http_msg.find("\r\n");
  std::string target = http_msg.substr(0, end);
  std::string first_field = target.substr(0, target.find(SPACE));
  if (first_field.find("HTTP") != std::string::npos) {
      return;
  } else if (first_field.empty()) {
    throw InvalidStartLine();
  }

  msg.setHeader("Method", first_field);
}

void HttpParser::parseHeader(Message & msg, std::string http_msg) {

}

void HttpParser::parseBody(Message & msg, std::string http_msg) {

}