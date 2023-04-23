#include <iostream>
#include <memory>
#include <cstring>
#include <assert.h>

#include "../srcs/HttpParser.hpp"
#include "../srcs/message.hpp"
#include "../srcs/response.hpp"


int main() {
  const char * http_request = "POST /login.php HTTP/1.1\r\n\
    Host: www.example.com\r\n\
    User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:88.0) Gecko/20100101 Firefox/88.0\r\n\
    Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n\
    Accept-Language: en-US,en;q=0.5\r\n\
    Accept-Encoding: gzip, deflate, br\r\n\
    Connection: keep-alive\r\n\
    Upgrade-Insecure-Requests: 1\r\n\
    Content-Type: application/x-www-form-urlencoded\r\
    Content-Length: 27\r\n\
    \r\n\
    username=johndoe&password=1234\r\n";

  HttpParser parser;
  MessageUniquePtr m = std::move(parser.parseRequest(http_request));

  // TOOD: do some assertion here
  assert(strncmp(m->getHeader().get("Method").c_str(), "POST", 5) == 0);
  std::cout << "request parsed success!!" << std::endl;

  const char * http_response = "HTTP/1.1 200 OK\r\n\
    Date: Fri, 22 Apr 2023 15:30:00 GMT\r\n\
    Server: Apache/2.4.18 (Ubuntu)\r\n\
    Last-Modified: Thu, 21 Apr 2023 12:00:00 GMT\r\n\
    ETag: \"abcde12345\"\r\n\
    Content-Length: 512\r\n\
    Content-Type: text/html\r\n\
    Connection: close\r\n\
    \r\n\
    <!DOCTYPE html>\
    <html>\
    <head>\
      <title>Welcome to Example.com</title>\
    </head>\
    <body>\
      <h1>Welcome to Example.com</h1>\
      <p>This is an example website.</p>\
    </body>\
    </html>\r\n";

  ResponseUniquePtr request = std::move(parser.parserResponse(http_response));
  // TODO: do some assertion here
  assert(request->getStatusCode() == HTTP_STATUS::HTTP_OK);
  std::cout << "response parsed success!!" << std::endl;
}