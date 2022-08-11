#ifndef _EC_STRING_UTIL_H_
#define _EC_STRING_UTIL_H_

#include <algorithm>
#include <queue>
#include <string>

namespace StringUtil {

  inline void rtrimChar(std::string& str, char ch) {
    str.erase(str.find_last_not_of(ch) + 1);
  }

  std::queue<std::string> SplitNumAndSign(const std::string& expression);

} // namespace StringUtil

#endif