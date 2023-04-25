#include <iostream>
#include <string>
#include <string.h>
#include <cstdlib>

#include "HttpParser.hpp"
#include "response.hpp"

MessagePtr HttpParser::parseRequest(std::string http_msg) {
  MessagePtr toRet = this->parseRequestStartLine(http_msg);
  this->parseHeader(toRet, http_msg);
  this->parseBody(toRet, http_msg);
  
  return toRet;
}

MessagePtr HttpParser::parseRequestStartLine(std::string http_msg) {
  size_t end = http_msg.find("\r\n");
  std::string firstLine = http_msg.substr(0, end);

  if (!isValidHttpFormat(firstLine) || isResponse(firstLine)) {
      throw InvalidHTTPFormat("Invalid HTTP Request Format");
  }

  MessagePtr msg = std::make_shared<Message>();
  msg->setHeader("Method", extractMethod(firstLine));
  return msg;
}

ResponsePtr HttpParser::parseResponse(std::string http_msg) {
  ResponsePtr response = this->parseResponseStartLine(http_msg);
  this->parseHeader(response, http_msg);
  this->parseBody(response, http_msg);
  return response;
}

ResponsePtr HttpParser::parseResponseStartLine(std::string http_msg) {
  size_t end = http_msg.find("\r\n");
  std::string firstLine = http_msg.substr(0, end);

  if(!isValidHttpFormat(firstLine) || !isResponse(firstLine)) {
    throw InvalidHTTPFormat("Invalid HTTP Response");
  }

  ResponsePtr msg = std::make_shared<Response>();
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

void HttpParser::parseHeader(MessagePtr msg, std::string http_msg) {
  std::string headerStr = extractHeader(http_msg);

  const char * header_cstr = headerStr.c_str();
  const char * start = header_cstr;
  const char * end = start + strlen(header_cstr);

  while (start < end) {
    const char * end_of_line = strstr(start, "\r\n");
    if (end_of_line == NULL) { break; }
    const char * end_of_field = strstr(start, ":");
    if (end_of_field == NULL) { break; }
    std::string field(start, end_of_field - start);
    std::string value(getNextAlphabetInStr(end_of_field + 1), end_of_line - getNextAlphabetInStr(end_of_field + 1));
    msg->setHeader(field, value);
    start = start + (end_of_line - start) + strlen("\r\n");
  }
}

const char * getNextAlphabetInStr(const char * str) {
  const char * ptr = str;
  while (ptr != NULL && std::isspace(*ptr)) { ptr++; }
  return ptr;
}

std::string HttpParser::extractHeader(std::string http_msg) {
  const char * http_msg_cstr = http_msg.c_str();
  const char * start = strstr(http_msg_cstr, "\r\n");
  if (start == NULL) { 
      throw InvalidHTTPFormat("Invalid Header");
  }
  start += strlen("\r\n");

  const char * end = strstr(start, "\r\n\r\n");
  if (end == NULL) { 
    throw InvalidHTTPFormat("Invalid Header");
  }

  size_t len = end - (start) + 2 + 1; // inlcude one \r\n and its 0 index
  char * buf = (char*)malloc(sizeof(*buf) * (len + 1)); // include \0
  strncpy(buf, start, len);
  buf[len] = '\0';

  std::string header(buf);
  free(buf);

  return header;
}

void HttpParser::parseBody(MessagePtr msg, std::string http_msg) {
  const char * http_msg_cstr = http_msg.c_str();
  const char * start = strstr(http_msg_cstr, "\r\n\r\n");
  if (start == NULL) { return; }
  start += strlen("\r\n\r\n");

  const char * ptr = start;
  const char * line_end = NULL;
  while ((line_end = strstr(ptr, "\n")) != NULL) {
    ptr += (line_end - ptr) + 1;
  }
  
  std::string body(start, ptr - start + 1);
  msg->setBody(body);
}


InvalidHTTPFormat::InvalidHTTPFormat(std::string _msg) : msg(_msg) {
  
}

const char * InvalidHTTPFormat::what() const noexcept {
  return msg.c_str();
}
