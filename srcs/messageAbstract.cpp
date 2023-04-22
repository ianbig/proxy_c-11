#include "messageAbstract.hpp"


messageAbstract::messageAbstract(HTTP_METHOD _method) : method(_method) {
  
}

std::string messageAbstract::getMessage() {
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
void messageAbstract::setHeader(std::string key, std::string val) {
  this->http_headers.set(key, val);
}

Header<std::string, std::string> & messageAbstract::getHeader() {
  return this->http_headers;
}

/**
 * @exception: FieldNotFoundException, invalid_argument, out_of_range
*/
size_t messageAbstract::getContentLength() {
  return std::stoi(this->http_headers.get("Content-Length"));
}

HTTP_METHOD messageAbstract::getMethod() {
  return method;
}