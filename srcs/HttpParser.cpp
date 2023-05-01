#include <iostream>
#include <string>
#include <string.h>
#include <cstdlib>

#include "HttpParser.hpp"
#include "response.hpp"

Message HttpParser::parseRequest(std::string http_msg) {
  Message toRet = this->parseRequestStartLine(http_msg);
  this->parseHeader(toRet, http_msg);
  this->parseBody(toRet, http_msg);
  toRet.setRaw(http_msg);
  
  return toRet;
}

Message HttpParser::parseRequestStartLine(std::string http_msg) {
  size_t end = http_msg.find("\r\n");
  std::string firstLine = http_msg.substr(0, end);

  if (!isValidHttpFormat(firstLine) || isResponse(firstLine)) {
      throw InvalidHTTPFormat("Invalid HTTP Request Format");
  }

  Message msg;
  msg.setHeader("Method", extractMethod(firstLine));
  return msg;
}

Response HttpParser::parseResponse(std::string http_msg) {
  Response response = this->parseResponseStartLine(http_msg);
  this->parseHeader(response, http_msg);
  this->parseBody(response, http_msg);
  response.setRaw(http_msg);
  
  return response;
}

Response HttpParser::parseResponseStartLine(std::string http_msg) {
  size_t end = http_msg.find("\r\n");
  std::string firstLine = http_msg.substr(0, end);

  if(!isValidHttpFormat(firstLine) || !isResponse(firstLine)) {
    throw InvalidHTTPFormat("Invalid HTTP Response");
  }

  Response msg;
  int code = extractedCode(firstLine);
  msg.setStatusCode(code);
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

void HttpParser::parseHeader(Message & msg, std::string http_msg) {
  const char * http_msg_cstr = http_msg.c_str();
  const char * start = strstr(http_msg_cstr, "\r\n");
  if (start == NULL) { 
      throw InvalidHTTPFormat("Invalid Header");
  }
  start += strlen("\r\n");

  const char * line_end = NULL;
  while ((line_end = strstr(start, "\r\n")) != NULL && (start != line_end)) {
    std::string field = extractFieldInLine(start);
    std::string value = extractValueInLine(start);
    msg.setHeader(field, value);
    start = line_end + strlen("\r\n");
  }
}

const char * getNextAlphabetInStr(const char * str) {
  const char * ptr = str;
  while (ptr != NULL && std::isspace(*ptr)) { ptr++; }
  return ptr;
}

std::string HttpParser::extractFieldInLine(const char * line) {
  const char * delim = strstr(line, ":");
  if (!delim) {
    throw InvalidHTTPFormat("Invalid Header");
  }

  return std::string(line, delim - line);
}

std::string HttpParser::extractValueInLine(const char * line) {
  const char * delim = strstr(line, ":");
  if (!delim) {
    throw InvalidHTTPFormat("Invalid Header");
  }

  const char * start = getNextAlphabetInStr(delim + 1);
  const char * end = strstr(start, "\r\n");
  if (!end) {
    throw InvalidHTTPFormat("Invalid Header");
  }

  return std::string(start, end - start);
}

const char * skipSpace(const char * start) {
  while (std::isspace(*start)) {
    start++;
  }
  return start;
}

void HttpParser::parseBody(Message & msg, std::string http_msg) {
  const char * http_msg_cstr = http_msg.c_str();
  const char * start = strstr(http_msg_cstr, "\r\n\r\n");
  if (start == NULL) { return; }
  start = skipSpace(start);

  const char * ptr = start;
  const char * line_end = NULL;
  while ((line_end = strstr(ptr, "\n")) != NULL) {
    ptr += (line_end - ptr) + 1;
  }
  
  std::string body(start, ptr - start + 1);
  msg.setBody(body);
}


InvalidHTTPFormat::InvalidHTTPFormat(std::string _msg) : msg(_msg) {
  
}

const char * InvalidHTTPFormat::what() const noexcept {
  return msg.c_str();
}
