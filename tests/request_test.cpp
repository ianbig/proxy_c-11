#include <string>
#include <iostream>
#include "assert.h"
#include <cstring>

#include "../srcs/getRequest.hpp"
#include "../srcs/postRequest.hpp"
#include "../srcs/connectRequest.hpp"

int main() {
  getRequest g;
  g.setHeader("Content-Length", "1000");
  g.setHeader("Method", "GET");
  g.setHeader("HOST", "www.google.com");
  g.setHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:98.0) Gecko/20100101 Firefox/98.0");
  
  assert(g.getContentLength() == 1000);
  assert(g.getMethod() == HTTP_METHOD::HTTP_GET);
  assert(g.getHeader().get("HOST") == "www.google.com");
  assert(g.getHeader().get("User-Agent") == "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:98.0) Gecko/20100101 Firefox/98.0");
  std::cout << "Abstract class requestAbstract method tested" << std::endl;

  // test getRequest Rule of five
  assert(g.getMethod() == HTTP_METHOD::HTTP_GET);
  getRequest g2 = g;
  assert(g2.getMessage() == g.getMessage());
  std::cout << "Class getRequest Copy Constructor passed" << std::endl;

  getRequest g3 = std::move(g2);
  assert(g2.getMessage() == "");
  assert(g3.getContentLength() == 1000);
  assert(g3.getMethod() == HTTP_METHOD::HTTP_GET);
  assert(g3.getHeader().get("HOST") == "www.google.com");
  assert(g3.getHeader().get("User-Agent") == "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:98.0) Gecko/20100101 Firefox/98.0");
  std::cout << "Class getRequest Move Constructor passed" << std::endl;

  getRequest g4;
  g4.setHeader("HOST", "www.linkedin.com");
  assert(g4.getHeader().get("HOST") == "www.linkedin.com");

  g4 = std::move(g3);
  assert(g3.getMessage() == "");
  assert(g4.getContentLength() == 1000);
  assert(g4.getMethod() == HTTP_METHOD::HTTP_GET);
  assert(g4.getHeader().get("HOST") == "www.google.com");
  assert(g4.getHeader().get("User-Agent") == "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:98.0) Gecko/20100101 Firefox/98.0");
  std::cout << "Class getRequest Move operator= passed" << std::endl;

  postRequest p;
  p.setBody("Ian is handsome");
  assert(strncmp(p.getBody(), "Ian is handsome", 16) == 0);
  std::cout << "Class postRequest getBody() and setBody() passed" << std::endl;


  connectRequest c;
  std::cout << "Class connectRequest passed" << std::endl;
}