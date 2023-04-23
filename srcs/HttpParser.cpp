#include <iostream>
#include <string>

#include "HttpParser.hpp"
#include "response.hpp"

MessageUniquePtr HttpParser::parseRequest(std::string http_msg) {
  MessageUniquePtr toRet = this->parseRequestStartLine(http_msg);
    // this->parseHeader(toRet, http_msg);
    // this->parseBody(toRet, http_msg);

  return toRet;
}

MessageUniquePtr HttpParser::parseRequestStartLine(std::string http_msg) {
  size_t end = http_msg.find("\r\n");
  std::string firstLine = http_msg.substr(0, end);

  if (!isValidHttpFormat(firstLine) || isResponse(firstLine)) {
      throw InvalidHTTPFormat("Invalid HTTP Request Format");
  }

  MessageUniquePtr msg = std::make_unique<Message>();
  msg->setHeader("Method", extractMethod(firstLine));
  return msg;
}

ResponseUniquePtr HttpParser::parserResponse(std::string http_msg) {
  size_t end = http_msg.find("\r\n");
  std::string firstLine = http_msg.substr(0, end);

  if(!isValidHttpFormat(firstLine) || !isResponse(firstLine)) {
    throw InvalidHTTPFormat("Invalid HTTP Response");
  }

  ResponseUniquePtr msg = std::make_unique<Response>();
  int code = extractedCode(firstLine);
  msg->setStatusCode(code);
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