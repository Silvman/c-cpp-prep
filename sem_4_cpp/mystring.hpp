#ifndef _MYSTRING_H_
#define _MYSTRING_H_

#include <iostream>

class mystring {
private:
  char* str;
  int len;

public:
  mystring();
  mystring(const char* text);
  mystring(const mystring& B);

  mystring& operator = (const mystring& from);
  mystring& operator = (const char*     from);

  mystring operator + (const char b);
  mystring operator + (const char* b);
  mystring operator + (const mystring& b);

  int length() const;

  const char* getstr() const;

  ~mystring();
};

std::ostream& operator << (std::ostream& os, const mystring& b);

#endif
