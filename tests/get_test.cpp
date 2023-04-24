#include <iostream>
#include <memory>

#include "../srcs/Get.hpp"

int main() {
  std::unique_ptr<ConnectionInterface> connection = std::make_unique<Get>();
  try {
    connection->connectToHost("www.google.com");
    // Response res = connection->recv();
    // TODO: test header, body with postman result
  } catch (GetSocketException & e) {
    std::cerr << "test failed: " << e.what() << std::endl;
  }
}