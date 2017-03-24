#include "stdafx.h"
#include <iostream>
#include <cstring>

using namespace std;

class pstring {
private:
  char* str;
  int len;

public:
  pstring();
  pstring(const char* text);
  pstring(const pstring& B);

  pstring& operator = (const pstring& from);
  pstring& operator = (const char*     from);

  pstring& operator + (const char b);
  pstring& operator + (const char* b);
  pstring& operator + (const pstring& b);

  pstring& operator += (const char b);
  pstring& operator += (const char* b);
  pstring& operator += (const pstring& b);

  pstring getByIndex(int a, int b) const;

  int length() const;

  // аналоги strcmp
  bool operator == (const pstring& b) const;
  bool operator > (const pstring& b) const;
  bool operator < (const pstring& b) const;

  const char* getstr() const;

  ~pstring();
};

ostream& operator << (ostream& os, const pstring& b);


int main () {
  pstring a = "Test string.";
  a += "arararar";
  a = a + 'c';
  pstring b(a);
  int t, n;
  cin >> t;
  n = b.length();



  cout << b.getByIndex(t, n) << endl;
  return 0;
}


pstring::pstring() {
  str = new char[1];
  str[0] = '\0';
  len = 0;
}

pstring::pstring(const char* text) {
  len = strlen(text);
  str = new char[len + 1];
  strcpy(str, text);
  str[len] = '\0';
}

pstring::pstring(const pstring& B) {
  len = B.len;
  str = new char[len + 1];
  strcpy(str, B.str);
  str[len] = '\0';
}

pstring& pstring::operator = (const pstring& from) {
  if (this == &from)
    return *this;

  delete[] str;
  len = from.len;
  str = new char[len + 1];
  strcpy(str, from.str);

  return *this;
}

pstring& pstring::operator = (const char* from) {
  delete[] str;
  len = strlen(from);
  str = new char[len + 1];
  strcpy(str, from);

  return *this;
}

pstring& pstring::operator + (const char* b) {
  int len_b = strlen(b);
  char* new_str = new char[len + len_b + 1];
  strncpy(new_str, str, len);
  strncpy(new_str + len, b, len_b);
  delete[] str;

  len = len + len_b;
  new_str[len] = '\0';
  str = new_str;

  return *this;
}

pstring& pstring::operator + (const char b) {
  len = len + 1;
  char* new_str = new char[len + 1];
  strncpy(new_str, str, len - 1);
  new_str[len - 1] = b;
  new_str[len] = '\0';

  delete[] str;
  str = new_str;

  return *this;
}

pstring& pstring::operator + (const pstring& b) {
  *this = *this + b.str;
  return *this;
}

pstring& pstring::operator += (const char b) {
  *this = *this + b;
  return *this;
}

pstring& pstring::operator += (const char* b) {
  *this = *this + b;
  return *this;
}

pstring& pstring::operator += (const pstring& b) {
  *this = *this + b;
  return *this;
}

pstring pstring::getByIndex(int a, int b) const {
  pstring buf;

  if ((a <= b) && (a >= 0) && (b > 0) && (b <= len)) {
    char instr[b - a + 1];

    for (int i = a; i < b; i++)
      instr[i - a] = str[i];
    instr[b - a] = '\0';

    buf += instr;
  }

  return buf;
}

bool pstring::operator == (const pstring& b) const {
  if(len == b.len)
    if(strncmp(str, b.str, len) == 0) return true;

  return false;
}

bool pstring::operator > (const pstring& b) const {
  size_t temp;
  if(len < b.len)
    temp = len;
  else
    temp = b.len;

  if(strncmp(str, b.str, temp) > 0) return true;

  return false;
}

bool pstring::operator < (const pstring& b) const {
  size_t temp;
  if(len < b.len)
    temp = len;
  else
    temp = b.len;

  if(strncmp(str, b.str, temp) < 0) return true;

  return false;
}

const char* pstring::getstr() const {
  return str;
}

int pstring::length() const {
  return len;
}

pstring::~pstring() {
  delete[] str;
}

ostream& operator << (ostream& os, const pstring& b) {
  os << b.getstr();
  return os;
}
