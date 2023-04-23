#include "response.hpp"


const char * Response::getBody() {
  return body.c_str();
}

HTTP_STATUS Response::getStatusCode() {
  return statusCode;
}

void Response::setBody(const char * _body) {
  this->body = _body;
}

void Response::setStatusCode(int status) {
  statusCode = (HTTP_STATUS)status;
}