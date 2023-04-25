#ifndef __get_hpp__
#define __get_hpp__

#include <iostream>
#include <string>
#include <exception>
#include "ConnectionInterface.hpp"

class GetSocketException: public std::exception {
  std::string msg;
  public:
  GetSocketException(std::string _msg);
  const char * what() const noexcept;
};

class Get : public ConnectionInterface {
  private:
  int socketfd;
  void setupConnection(const char * hostname, const char * port) override;
  public:
  void connectToHost(std::string hostname) override;
  void sendToHost(Message msg) override;
  Response recvFromHost() override;
};

#endif