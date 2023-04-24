#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>

#include "Get.hpp"

GetSocketException::GetSocketException(std::string _msg) : msg(_msg)  {}

const char * GetSocketException::what() const noexcept {
  return this->msg.c_str();
}

void Get::connectToHost(std::string hostname) {
  size_t hostNameEndIndex = hostname.find(":");
  std::string host = hostname;
  std::string port = "3000";
  if (hostNameEndIndex != std::string::npos) {
    host = hostname.substr(0, hostNameEndIndex);
    port = hostname.substr(hostNameEndIndex + 1);
  }

  this->setupConnection(host.c_str(), port.c_str());
}

void Get::setupConnection(const char * hostname, const char * port) {
  struct addrinfo hints, *serverinfo, *p;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  int rv = -1;
  if ((rv = getaddrinfo("www.google.com", NULL, &hints, &serverinfo)) != 0) {
    throw GetSocketException(std::string("Unable to setup Get Connection: ") + gai_strerror(rv));
  }

  int socketfd = -1;
  for (p = serverinfo; p != NULL; p = p->ai_next) {
    if ((socketfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
      perror("fail to create socket fd");
      continue;
    }

    std::cout << socketfd << std::endl;
    if (connect(socketfd, p->ai_addr, p->ai_addrlen) == -1) {
      close(socketfd);
      perror("fail to connect");
      continue;
    }

    std::cout << "1" << std::endl;
    break;
  }

  if (p == NULL) {
    throw GetSocketException("Get Socket: fail to connect");
  }

  free(serverinfo);
}


void Get::sendToHost(Message msg) {

}

Response Get::recvFromHost() {
  return Response();
}