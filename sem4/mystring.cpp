#include <iostream>
#include <cstring>
#include "mystring.hpp"

mystring::mystring() {
  try {
    str = new char[1];
    str[0] = '\0';
    len = 0;
  } catch (const std::bad_alloc &ba) {
    std::cerr << ba.what() << std::endl;
  }
}

mystring::mystring(const char* text) {
  try {
    len = strlen(text);
    str = new char[len + 1];
    strcpy(str, text);
    str[len] = '\0';
  } catch (const std::bad_alloc &ba) {
    std::cerr << ba.what() << std::endl;
    delete this;
  }
}

mystring::mystring(const mystring& B) {
  try {
    len = B.len;
    str = new char[len + 1];
    strcpy(str, B.str);
    str[len] = '\0';
  } catch (const std::bad_alloc &ba) {
    std::cerr << ba.what() << std::endl;
    delete this;
  }
}

mystring& mystring::operator = (const mystring& from) {
  if (this == &from)
    return *this;

  delete[] str;
  try {
    len = from.len;
    str = new char[len + 1];
    strcpy(str, from.str);

    return *this;
  } catch (const std::bad_alloc &ba) {
    std::cerr << ba.what() << std::endl;
    delete this;
  }
}

mystring& mystring::operator = (const char* from) {
  delete[] str;
  try {
    len = strlen(from);
    str = new char[len + 1];
    strcpy(str, from);

    return *this;
  } catch (const std::bad_alloc &ba) {
    std::cerr << ba.what() << std::endl;
    delete this;
  }
}

mystring mystring::operator + (const char* b) {
  try {
    mystring a;
    int len_b = strlen(b);
    char* new_str = new char[len + len_b + 1];
    strncpy(new_str, str, len);
    strncpy(new_str + len, b, len_b);

    a.len = len + len_b;
    new_str[a.len] = '\0';
    delete[] a.str;
    a.str = new_str;

    return a;
  } catch (const std::bad_alloc &ba) {
    std::cerr << ba.what() << std::endl;
    throw;
  }
}

mystring mystring::operator + (const char b) {
  try {
    mystring a;
    a.len = len + 1;
    char* new_str = new char[len + 1];
    strncpy(new_str, str, len - 1);
    new_str[len - 1] = b;
    new_str[len] = '\0';

    delete[] a.str;
    a.str = new_str;

    return a;
  } catch (const std::bad_alloc &ba) {
    std::cerr << ba.what() << std::endl;
    delete this;
    throw;
  }
}

mystring mystring::operator + (const mystring& b) {
  try {
    mystring a = *this + b.str;
    return a;
  } catch (const std::bad_alloc &ba) {
    throw;
  }
}

const char* mystring::getstr() const {
  return str;
}

int mystring::length() const {
  return len;
}

mystring::~mystring() {
  delete[] str;
}

std::ostream& operator << (std::ostream& os, const mystring& b) {
  os << b.getstr();
  return os;
}
