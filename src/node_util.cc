#include "node_util.h"

using namespace std;
namespace nodeutil {
  // 暂时只分两种优先级，高优先级为*/，低优先级为+-，暂不提供括号()功能。
  // 未检查表达式是否错误、无解。
  // NOTE: 遍历次数多，性能较差!
  Node buildExpression(queue<string>& expressions) {
    vector<Node> all_nodes;
    vector<string> opers;

    // parse expressions
    size_t size = expressions.size();
    while (size != 0) {
      double value = stod(expressions.front());
      expressions.pop();
      Node node(value);
      all_nodes.push_back(node);
      --size;

      if (size == 0) // 处理完成
      {
        break;
      } else {
        string oper = expressions.front();
        expressions.pop();
        opers.push_back(oper);
        --size;
      }
    }

    // step 1. 处理*/运算符
    for (size_t index = 0; index != opers.size(); ++index) {
      if (opers[index] == "*" || opers[index] == "/") {
        Node new_node;
        if (opers[index] == "*") {
          new_node = all_nodes[index] * all_nodes[index + 1];
        } else { // opers[index] == "/"
          new_node = all_nodes[index] / all_nodes[index + 1];
        }

        all_nodes.erase(all_nodes.begin() + index,
                        all_nodes.begin() + index + 2);
        all_nodes.insert(all_nodes.begin() + index, new_node);

        opers.erase(opers.begin() + index);
        index = 0; // 重置index
        continue;  // 由于all_nodes和opers都变化了，所以要退出。
      }
    }

    // step 2. 处理+-运算符
    Node root_node = all_nodes[0];
    size_t node_index = 0;

    for (size_t oper_index = 0; oper_index != opers.size(); ++oper_index) {
      node_index = oper_index + 1;
      if (opers[oper_index] == "+") {
        root_node = root_node + all_nodes[node_index];
      }
      if (opers[oper_index] == "-") {
        root_node = root_node - all_nodes[node_index];
      }
    }

    return root_node;
  }
} // namespace nodeutil
