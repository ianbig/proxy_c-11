#ifndef __requestAbstract_hpp__
#define __requestAbstract_hpp__

#include <string>
#include "header.hpp"
#include "messageInterface.hpp"
#include "httpInfo.hpp"

class requestAbstract : public messageInterface {
  protected:
  Header<std::string, std::string> http_headers;
  HTTP_METHOD method;
  public:
  requestAbstract(HTTP_METHOD method);
  requestAbstract(const requestAbstract & rhs) = default;
  requestAbstract(requestAbstract && rhs) noexcept = default;

  requestAbstract& operator=(const requestAbstract & rhs) = default;
  requestAbstract& operator=(requestAbstract && rhs) noexcept = default;

  virtual std::string getMessage() override;
  virtual void setHeader(std::string key, std::string val) override;
  virtual Header<std::string, std::string> & getHeader() override;
  virtual size_t getContentLength() override;
  virtual HTTP_METHOD getMethod() override;
};

#endif