#ifndef __getRequest_hpp__
#define __getRequest_hpp__


#include "messageAbstract.hpp"

class getRequest: public messageAbstract {
  public:
  getRequest();
  getRequest(const getRequest & rhs) = default;
  getRequest(getRequest && rhs) noexcept = default;

  getRequest& operator=(const getRequest & rhs) = default;
  getRequest& operator=(getRequest && rhs) = default;
};

#endif