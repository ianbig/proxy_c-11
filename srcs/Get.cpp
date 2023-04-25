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
#include "HttpParser.hpp"


GetSocketException::GetSocketException(std::string _msg) : msg(_msg)  {}

const char * GetSocketException::what() const noexcept {
  return this->msg.c_str();
}

void Get::connectToHost(std::string hostname) {
  size_t hostNameEndIndex = hostname.find(":");
  std::string host = hostname;
  std::string port = "80";
  if (hostNameEndIndex != std::string::npos) {
    host = hostname.substr(0, hostNameEndIndex);
    port = hostname.substr(hostNameEndIndex + 1);
  }

  this->setupConnection(host.c_str(), port.c_str());
}

void Get::setupConnection(const char * hostname, const char * port) {
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  int rv = -1;
  struct addrinfo * serverinfo;
  if ((rv = getaddrinfo(hostname, port, &hints, &serverinfo)) != 0) {
    throw GetSocketException(std::string("Unable to setup Get Connection: ") + gai_strerror(rv));
  }

  struct addrinfo * p = NULL;
  for (p = serverinfo; p != NULL; p = p->ai_next) {
    if ((this->socketfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
      perror("fail to create socket fd");
      continue;
    }

    if (connect(this->socketfd, p->ai_addr, p->ai_addrlen) == -1) {
      close(socketfd);
      perror("fail to connect");
      continue;
    }

    break;
  }

  if (p == NULL) {
    throw GetSocketException("Get Socket: fail to connect");
  }

  free(serverinfo);
}


void Get::sendToHost(Message msg) {
  std::string msg_to_send_str = msg.getMessage();
  const char * msg_to_send = msg_to_send_str.c_str();
  size_t bytes_to_sent = msg.getMessage().size();
  size_t cur_send_bytes = -1;
  while ((msg_to_send && bytes_to_sent > 0) && (cur_send_bytes = send(this->socketfd, msg_to_send, bytes_to_sent, 0)) != -1) {
    bytes_to_sent -= cur_send_bytes;
    msg_to_send += cur_send_bytes;
  }

  if (bytes_to_sent > 0) {
    throw GetSocketException("sendToHost: GetSocket send request incomplete");
  }
}

Response Get::recvFromHost() {
  size_t num_bytes_recv = 0;
  char * buf = (char*)malloc(sizeof(*buf) * DEFAULT_MAX_SZ);
  if ((num_bytes_recv = recv(this->socketfd, buf, DEFAULT_MAX_SZ - 1, 0)) == -1) {
    throw GetSocketException("get recv: error on receving headers");
  }
  buf[num_bytes_recv] = '\0';
  HttpParser parser;
  ResponsePtr r = parser.parseResponse(buf);
  size_t response_sz = -1;
  try {
    // TODO: minus something here
    size_t header_sz = r->getMessage().size() - r->getContentLength();
    response_sz = r->getContentLength() + header_sz;
  } catch (FieldNotFoundException<std::string> & e) {
    // TODO: if no content length
  }

  size_t cur_recv = -1;
  size_t max_bytes = DEFAULT_MAX_SZ;
  char tmpBuf[DEFAULT_MAX_SZ];
  while (num_bytes_recv < response_sz) {
    if ((cur_recv = recv(this->socketfd, tmpBuf, DEFAULT_MAX_SZ - 1, 0)) == -1) {
      throw GetSocketException("get recv: error on receving headers");
    }
    tmpBuf[cur_recv] = '\0';
    num_bytes_recv += cur_recv;
    if (num_bytes_recv >= max_bytes) {
      max_bytes *= 2;
      buf = (char*)realloc(buf, sizeof(*buf) * max_bytes);
    }
    strcat(buf, tmpBuf);
  }
  r = parser.parseResponse(buf);
  free(buf);

  return *r;
}
