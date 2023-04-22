#ifndef __connectRequest_hpp__
#define __connectRequest_hpp__

#include "requestAbstract.hpp"

class connectRequest: public requestAbstract {
  public:
  connectRequest();
  connectRequest(const connectRequest & rhs) = default;
  connectRequest(connectRequest && rhs) = default;

  connectRequest& operator=(connectRequest & rhs) = default;
  connectRequest& operator=(connectRequest && rhs) = default;
};

#endif