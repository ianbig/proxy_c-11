#include <string>
#include <assert.h>

#include "../srcs/header.hpp"

int main() {
  Header<std::string, std::string> headers;
  // Basic Test
  headers.set("Method", "POST");
  headers.set("Content-Length", "1000");
  headers.set("Host", "www.google.com");
  assert(headers.get("Method") == "POST");
  assert(headers.get("Host") == "www.google.com");
  assert(headers.get("Content-Length") == "1000");
  std::cout << "Basic Testing Passed" << std::endl;
  // Test Rule of Five
  Header<std::string, std::string> headers_copy = headers;
  assert(headers_copy.get("Method") == "POST");
  assert(headers_copy.get("Host") == "www.google.com");
  assert(headers_copy.get("Content-Length") == "1000");
  std::cout << "Copy Constructor passed" << std::endl;
  assert(headers_copy == headers);
  std::cout << "Assignment operator passed" << std::endl;

  Header<std::string, std::string> headers_moved = std::move(headers);
  assert(headers_moved == headers_copy);
  try {
    std::string res = headers.get("Method");
    std::cout << "Move Construction failed, get result: " << res << std::endl;
  } catch (FieldNotFoundException<std::string> & e) {
    std::cout << "Move Construction passed" << std::endl;
  }

  Header<std::string, std::string> to_moved;
  to_moved.set("Host", "www.linkedin.com");
  headers_moved = std::move(to_moved);
  assert(headers_moved.get("Host") == "www.linkedin.com");
  try {
    std::string res = to_moved.get("Method");
    std::cout << "Move Assignment failed, get result: " << res << std::endl;
  } catch (FieldNotFoundException<std::string> & e) {
    std::cout << "Move Assignment passed" << std::endl;
  }

  for (auto it = headers_moved.begin(); it != headers_moved.end(); it++) {
    assert(it->first == "Host");
    assert(it->second == "www.linkedin.com");
  }
  std::cout << "Iterator passed" << std::endl;

  headers_moved.set("Host", "www.google.com");
  assert(headers_moved.get("Host") == "www.google.com");
  std::cout << "Duplicate set method passed!" << std::endl;
}