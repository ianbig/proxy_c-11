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
  using Iterator = typename std::unordered_map<K, V>::iterator;
  HashMap headers;
  public:
  Header() = default;
  ~Header() = default;
  Header(const Header & rhs) = default;
  Header(Header && rhs) noexcept = default;
  Header & operator=(const Header & rhs) = default;
  Header & operator=(Header && rhs) noexcept = default;
  bool operator==(Header & rhs) {
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

  Iterator begin() {
    return headers.begin();
  }

  Iterator end() {
    return headers.end();
  }
};

#endif