#ifndef _EC_NODE_UTIL_H_
#define _EC_NODE_UTIL_H_
#include "node.h"
#include <queue>
#include <string>

namespace nodeutil {
  Node buildExpression(std::queue<std::string>& expressions);
  void parseExpression(std::queue<std::string>& expressions,
                       std::vector<Node>& all_nodes,
                       std::vector<std::string>& opers);
  void processMulAndDiv(std::vector<Node>& all_nodes,
                        std::vector<std::string>& opers);
  Node processAddAndMinus(std::vector<Node>& all_nodes,
                          std::vector<std::string>& opers);
} // namespace nodeutil
#endif