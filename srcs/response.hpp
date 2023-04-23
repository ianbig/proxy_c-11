#ifndef __response_hpp__
#define __response_hpp__

#include <string>

#include "message.hpp"
#include "httpInfo.hpp"

class Response : public Message {
  protected:
  HTTP_STATUS statusCode;
  public:
  Response() = default;
  Response(const Response & rhs) = default;
  Response(Response&& rhs) = default;
  ~Response() = default;

  Response& operator=(const Response & rhs) = default;
  Response& operator=(Response && rhs) = default;

  void setStatusCode(int statusCode);
  HTTP_STATUS getStatusCode();
};

#endif