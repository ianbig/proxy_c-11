#include "response.hpp"

HTTP_STATUS Response::getStatusCode() {
  return statusCode;
}

void Response::setStatusCode(int status) {
  statusCode = (HTTP_STATUS)status;
}