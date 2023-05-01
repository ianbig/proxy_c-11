#include <iostream>
#include <memory>
#include <cstring>
#include <assert.h>

#include "../srcs/HttpParser.hpp"
#include "../srcs/message.hpp"
#include "../srcs/response.hpp"

void validateRequestHeader(Header<std::string, std::string> headers) {
  assert(headers.get("Host") == "www.example.com");
  assert(headers.get("User-Agent") == "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:88.0) Gecko/20100101 Firefox/88.0");
  assert(headers.get("Accept") == "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");
  assert(headers.get("Accept-Language") == "en-US,en;q=0.5");
  assert(headers.get("Accept-Encoding") == "gzip, deflate, br");
  assert(headers.get("Connection") == "keep-alive");
  assert(headers.get("Upgrade-Insecure-Requests") == "1");
  assert(headers.get("Content-Type") == "application/x-www-form-urlencoded");
  assert(headers.get("Content-Length") == "27");
}

void validateResponseHeader(Header<std::string, std::string> headers) {
  assert(headers.get("Date") == "Fri, 22 Apr 2023 15:30:00 GMT");
  assert(headers.get("Server") == "Apache/2.4.18 (Ubuntu)");
  assert(headers.get("Last-Modified") == "Thu, 21 Apr 2023 12:00:00 GMT");
  assert(headers.get("ETag") == "\"abcde12345\"");
  assert(headers.get("Content-Length") == "512");
  assert(headers.get("Content-Type") == "text/html");
  assert(headers.get("Connection") == "close");
}

void validateGetRequest(Header<std::string, std::string> headers) {
  assert(headers.get("Host") == "www.man7.org");
  assert(headers.get("User-Agent") == "Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:95.0) Gecko/20100101 Firefox/95.0");
  assert(headers.get("Accept") == "*/*");
  assert(headers.get("Accept-Encoding") == "gzip, deflate, br");
  assert(headers.get("Connection") == "keep-alive");
}


int main() {
  const char * http_request = "POST /login.php HTTP/1.1\r\n\
Host: www.example.com\r\n\
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:88.0) Gecko/20100101 Firefox/88.0\r\n\
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n\
Accept-Language: en-US,en;q=0.5\r\n\
Accept-Encoding: gzip, deflate, br\r\n\
Connection: keep-alive\r\n\
Upgrade-Insecure-Requests: 1\r\n\
Content-Type: application/x-www-form-urlencoded\r\n\
Content-Length: 27\r\n\
\r\n\
username=johndoe&password=1234\n\
apple\n";

  HttpParser parser;
  Message msg = parser.parseRequest(http_request);
  std::unique_ptr<Message> m = std::make_unique<Message>(msg);

  assert(strncmp(m->getHeader().get("Method").c_str(), "POST", 5) == 0);
  validateRequestHeader(m->getHeader());
  assert(strcmp(m->getBody(), "username=johndoe&password=1234\napple\n") == 0);
  assert(strcmp(m->getMessage(), http_request) == 0);

  std::string get_request =
      "GET /linux/man-pages/man2/recv.2.html HTTP/1.1\r\n\
Host: www.man7.org\r\n\
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:95.0) Gecko/20100101 Firefox/95.0\r\n\
Accept: */*\r\n\
Accept-Encoding: gzip, deflate, br\r\n\
Connection: keep-alive\r\n\r\n";
  Message resp = parser.parseRequest(get_request);
  std::unique_ptr<Message> get_m = std::make_unique<Message>(resp);
  validateGetRequest(get_m->getHeader());

  std::cout << "request parsed success!!" << std::endl << std::endl;

  const char * http_response = "HTTP/1.1 200 OK\r\n\
Date: Fri, 22 Apr 2023 15:30:00 GMT\r\n\
Server: Apache/2.4.18 (Ubuntu)\r\n\
Last-Modified: Thu, 21 Apr 2023 12:00:00 GMT\r\n\
ETag: \"abcde12345\"\r\n\
Content-Length: 512\r\n\
Content-Type: text/html\r\n\
Connection: close\r\n\r\n\
<!DOCTYPE html><html><head><title>Welcome to Example.com</title></head><body><h1>Welcome to Example.com</h1><p>This is an example website.</p></body></html>\n";

  Response response = parser.parseResponse(http_response);
  assert(response.getStatusCode() == HTTP_STATUS::HTTP_OK);
  validateResponseHeader(response.getHeader());
  assert(strcmp(response.getMessage(), http_response) == 0);

  std::cout << "response parsed success!!" << std::endl;
}