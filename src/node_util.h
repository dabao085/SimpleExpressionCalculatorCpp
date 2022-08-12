#ifndef _EC_NODE_UTIL_H_
#define _EC_NODE_UTIL_H_
#include "node.h"
#include <queue>
#include <string>

namespace nodeutil {
  Node buildExpression(std::queue<std::string>& expressions);
}
#endif