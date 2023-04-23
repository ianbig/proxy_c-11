#include "message.hpp"


Message::Message(HTTP_METHOD _method) : method(_method) {
  
}

std::string Message::getMessage() {
  std::string res = "";
  for (auto it = http_headers.begin(); it != http_headers.end(); it++) {
    res += it->first + ": " + it->second + "\n";
  }

  return res;
}

/**
 * @exception: default behavior std::bad_alloc, the exception is determined
 * by the excpetion of default allocator
*/
void Message::setHeader(std::string key, std::string val) {
  this->http_headers.set(key, val);
}

Header<std::string, std::string> & Message::getHeader() {
  return this->http_headers;
}

/**
 * @exception: FieldNotFoundException, invalid_argument, out_of_range
*/
size_t Message::getContentLength() {
  return std::stoi(this->http_headers.get("Content-Length"));
}

HTTP_METHOD Message::getMethod() {
  return method;
}