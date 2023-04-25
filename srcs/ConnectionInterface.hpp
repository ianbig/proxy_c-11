#ifndef __connection_interface_hpp__
#define __connection_interface_hpp__

#define DEFAULT_MAX_SZ 1024

#include <string>
#include "response.hpp"
#include "message.hpp"

class ConnectionInterface {
  private:
  virtual void setupConnection(const char * hostname, const char * port) = 0;
  public:
  virtual void connectToHost(std::string hostname) = 0;
  virtual void sendToHost(Message msg) = 0;
  virtual Response recvFromHost() = 0;
};

#endif