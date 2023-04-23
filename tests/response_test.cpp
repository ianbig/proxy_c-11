#include <cstring>
#include <assert.h>

#include "../srcs/response.hpp"
#include "../srcs/httpInfo.hpp"


int main() {
  Response r;
  r.setStatusCode(200);
  r.setBody("Ian is handsome");


  assert(r.getStatusCode() == HTTP_STATUS::HTTP_OK);
  assert(strncmp(r.getBody(), "Ian is handsome", strlen("Ian is handsome")) == 0);
  std::cout << "Class Response passed" << std::endl;
}