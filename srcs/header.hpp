#ifndef __header_hpp__
#define __header_hpp__

#include <iostream>
#include <string>
#include <unordered_map>
#include <exception>

template<typename K>
class FieldNotFoundException: public std::exception {
  private:
  K key;
  public:
  FieldNotFoundException(K key) {}
  virtual const char * what() const noexcept {
    std::string message = key + " not found";
    return message.c_str();
  }
};

template<typename K, typename V>
class Header {
  private:
  using HashMap = std::unordered_map<K, V>;
  HashMap headers;
  public:
  Header() = default;
  ~Header() = default;
  Header(const Header & rhs) : headers(rhs.headers) {}

  Header(Header && rhs) noexcept : headers(std::move(rhs.headers)) {}

  Header & operator=(const Header & rhs) const {
    if (this != & rhs) {
      this->headers = rhs.headers;
    }

    return *this;
  }

  Header & operator=(const Header && rhs) noexcept {
    if (this != &rhs) {
      this->headers = std::move(rhs.headers);
    }
    
    return *this;
  }

  bool operator==(Header & rhs) const {
    return this->headers == rhs.headers;
  }

  int set(K field, V val) {
    if (headers.find(field) == headers.end()) {
      headers[field] = val;
    }

    return 0; // means success
  }

  V get(K field) {
    if (headers.find(field) == headers.end()) {
      throw FieldNotFoundException<K>(field);
    }

    return headers[field];
  }
};

#endif