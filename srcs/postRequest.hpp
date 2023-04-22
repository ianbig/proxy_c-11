#ifndef __postRequest_hpp__
#define __postRequest_hpp__

#include "requestAbstract.hpp"

class postRequest : requestAbstract {
  std::string body;
  public:
  postRequest();
  postRequest(const postRequest & rhs) = default;
  postRequest(postRequest && rhs) noexcept = default;

  postRequest& operator=(const postRequest & rhs) = default;
  postRequest& operator=(postRequest && rhs) = default;
  void setBody(const char * _body);
  const char * getBody();
};

#endif