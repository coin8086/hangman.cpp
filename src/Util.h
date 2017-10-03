#ifndef __UTIL_H__
#define __UTIL_H__

#include <string>
#include <cctype>

using namespace std;

inline string toUpper(const string & str) {
  string ret(str);
  //NOTE: C++11 for
  for (char & ch : ret) {
    ch = toupper(ch);
  }
  return ret;
}

#endif
