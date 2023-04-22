#include "requestAbstract.hpp"

std::string requestAbstract::getMessage() {
  std::string res = "";
  for (auto it = headers.begin(); it != headers.end(); it++) {
  }

  return res;
}

int setHeader(std::string key, std::string val) {

}
// virtual Header<std::string, std::string> getHeader();
// virtual size_t getContentLength();
// virtual std::string getMethod();