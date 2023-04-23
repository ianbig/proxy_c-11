#include <iostream>
#include <string>

#include "HttpParser.hpp"
#include "response.hpp"

Message* HttpParser::parse(std::string http_msg) {
  Message* toRet = this->parseStartLine(http_msg);
    // this->parseHeader(toRet, http_msg);
    // this->parseBody(toRet, http_msg);

  return toRet;
}

Message* HttpParser::parseStartLine(std::string http_msg) {
  size_t end = http_msg.find("\r\n");
  std::string firstLine = http_msg.substr(0, end);

  if (isResponse(firstLine)) {
      Response * msg = new Response();
      int code = extractedCode(firstLine);
      msg->setStatusCode(code);
      return msg;
  } else if (!isValidHttpFormat(firstLine)) {
    throw InvalidHTTPFormat("Invalid start Line");
  }

  Message * msg = new Message();
  msg->setHeader("Method", extractMethod(firstLine));
  return msg;
}

bool HttpParser::isValidHttpFormat(std::string firstLine) {
  size_t first_space = firstLine.find(SPACE);
  std::string first_field = firstLine.substr(0, first_space);
  return isResponse(firstLine) || isRequest(first_field);
}

bool HttpParser::isResponse(std::string firstLine) {
  size_t first_space = firstLine.find(SPACE);
  std::string first_field = firstLine.substr(0, first_space);
  return first_field.find("HTTP") != std::string::npos;
}

bool HttpParser::isRequest(std::string method) {
  return method == "GET" || method == "POST" || method == "CONNECT";
}

int HttpParser::extractedCode(std::string firstLine) {
  size_t first_space = firstLine.find(SPACE);
  std::string extractedCode = firstLine.substr(first_space, firstLine.find(SPACE, first_space));
  return std::stoi(extractedCode);
}

std::string HttpParser::extractMethod(std::string firstLine) {
  size_t first_space = firstLine.find(SPACE);
  std::string first_field = firstLine.substr(0, first_space);
  return first_field;
}

InvalidHTTPFormat::InvalidHTTPFormat(std::string _msg) : msg(_msg) {
  
}

void HttpParser::parseHeader(Message * msg, std::string http_msg) {

}

// void HttpParser::parseBody(Message & msg, std::string http_msg) {

// }