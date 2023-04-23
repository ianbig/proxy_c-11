#ifndef __HTTPINFO_hpp__
#define __HTTPINFO_hpp__

enum class HTTP_METHOD {
  HTTP_GET,
  HTTP_POST,
  HTTP_CONNECT
};

enum class HTTP_STATUS {
  HTTP_OK = 200,
  HTTP_NOT_FOUND = 404
};

#endif