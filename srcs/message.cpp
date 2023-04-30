#include "message.hpp"

Message::Message(const char * msg) : raw(msg) {

}

Message::Message(HTTP_METHOD _method) : method(_method) {
  
}

const char * Message::getMessage() {
  return raw.c_str();
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

const char * Message::getBody() {
  return body.c_str();
}

void Message::setBody(std::string _body) {
  this->body = _body;
}


std::string Message::getHost() {
  return this->getHeader().get("Host");
}

void Message::setRaw(std::string _raw) {
  this->raw = _raw;
}