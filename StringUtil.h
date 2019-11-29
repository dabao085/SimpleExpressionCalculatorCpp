#ifndef _EC_STRING_UTIL_H_
#define _EC_STRING_UTIL_H_

#include <string>

namespace StringUtil
{

inline void rtrimChar(std::string& str, char ch)
{
    str.erase(str.find_last_not_of(ch) + 1);
}

}

#endif