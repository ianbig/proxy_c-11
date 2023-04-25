#include <string>
#include <iostream>
#include "assert.h"
#include <cstring>

#include "../srcs/message.hpp"

int main() {
  Message g;
  g.setHeader("Content-Length", "1000");
  g.setHeader("Method", "GET");
  g.setHeader("HOST", "www.google.com");
  g.setHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:98.0) Gecko/20100101 Firefox/98.0");
  g.setBody("I am Ian");
  
  assert(g.getContentLength() == 1000);
  assert(g.getHeader().get("HOST") == "www.google.com");
  assert(g.getHeader().get("User-Agent") == "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:98.0) Gecko/20100101 Firefox/98.0");
  std::cout << "Class request method tested" << std::endl;
}