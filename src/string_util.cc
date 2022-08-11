#include "string_util.h"
#include <iostream>

namespace StringUtil {
  // split expression by nums and operators
  std::queue<std::string> SplitNumAndSign(const std::string& expression) {
    std::queue<std::string> result;
    std::string str(expression);
    str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());

    std::string num;
    std::string oper;
    for (auto& a : str) {
      if (isdigit(a)) {
        if (!oper.empty()) {
          result.push(oper);
          oper.clear();
        }
        num.push_back(a);
      } else {
        if (!num.empty()) {
          result.push(num);
          num.clear();
        }
        oper = a;
      }
    }

    if (!num.empty()) { result.push(num); }

    return result;
  }
} // namespace StringUtil