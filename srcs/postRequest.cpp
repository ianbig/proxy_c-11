#include "postRequest.hpp"
#include "httpInfo.hpp"


postRequest::postRequest() : requestAbstract(HTTP_METHOD::HTTP_POST) {

}

void postRequest::setBody(const char * _body) {
  this->body = _body;
}

const char * postRequest::getBody() {
  return body.c_str();
}