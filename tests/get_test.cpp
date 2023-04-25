#include <iostream>
#include <memory>

#include "../srcs/HttpParser.hpp"
#include "../srcs/Get.hpp"

int main() {
  std::unique_ptr<ConnectionInterface> connection = std::make_unique<Get>();
  try {
    std::string request =
      "GET /linux/man-pages/man2/recv.2.html HTTP/1.1\r\n\
Host: www.man7.org\r\n\
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:95.0) Gecko/20100101 Firefox/95.0\r\n\
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8\r\n\
Accept-Language: zh-TW,zh;q=0.8,en-US;q=0.5,en;q=0.3\r\n\
Accept-Encoding: gzip, deflate\r\n\
Connection: keep-alive\r\n\r\n";
    try {
      HttpParser p;
      std::shared_ptr<Message> m = p.parseRequest(request);
      connection->connectToHost(m->getHost());
      connection->sendToHost(*m);
      Response res = connection->recvFromHost();
      std::cout << res.getMessage() << std::endl;
      std::cout << res.getMessage().size() << std::endl;
      // TODO: test header, body with postman result
    } catch (GetSocketException & e) {
      std::cerr << "test failed: " << e.what() << std::endl;
    }
  } catch (InvalidHTTPFormat & e) {
      std::cout << e.what() << std::endl;
  }

}