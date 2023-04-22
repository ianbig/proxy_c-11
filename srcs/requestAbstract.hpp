#ifndef __requestAbstract_hpp__
#define __requestAbstract_hpp__

#include <string>
#include "header.hpp"
#include "messageInterface.hpp"

class requestAbstract : public messageInterface {
  private:
  Header<std::string, std::string> headers;
  public:
  virtual std::string getMessage() override;
  
};

#endif