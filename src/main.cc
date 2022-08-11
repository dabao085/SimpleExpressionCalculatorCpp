#include "base/logging.h"
#include "binary_node.h"
#include "gflags/gflags.h"
#include <iostream>

using namespace std;

ostream& operator<<(ostream& os, const Node& node) { return os << node.rep(); }

// 暂时只分两种优先级，高优先级为*/，低优先级为+-，暂不提供括号()功能。
// 未检查表达式是否错误、无解。
// NOTE: 性能较差!
Node buildExpression(queue<string>& expressions) {
  vector<Node> all_nodes;
  vector<string> opers;

  // dispatch expressions
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

  // for(auto & a: all_nodes)
  // {
  //     cout << a << endl;
  // }

  //step 1. 处理*/运算符
  for (size_t index = 0; index != opers.size(); ++index) {
    if (opers[index] == "*" || opers[index] == "/") {
      if (opers[index] == "*") {
        Node newnode = all_nodes[index] * all_nodes[index + 1];
        all_nodes.erase(all_nodes.begin() + index,
                        all_nodes.begin() + index + 2);
        // cout << "newnode: " << newnode << endl;
        all_nodes.insert(all_nodes.begin() + index, newnode);

        opers.erase(opers.begin() + index);
        index = 0; // 重置index
        continue;  // 由于all_nodes和opers都变化了，所以要退出。
      }
      if (opers[index] == "/") {
        Node newnode = all_nodes[index] / all_nodes[index + 1];
        all_nodes.erase(all_nodes.begin() + index,
                        all_nodes.begin() + index + 2);
        // cout << "newnode: " << newnode << endl;
        all_nodes.insert(all_nodes.begin() + index, newnode);

        opers.erase(opers.begin() + index);
        index = 0; // 重置index
        continue;  // 由于all_nodes和opers都变化了，所以要退出。
      }
    }
  }
  // cout << "print all node after */: " << endl;
  // for(auto & a : all_nodes)
  // {
  //     cout << a << " : " << a.calculate() << endl;
  // }
  // cout << endl;

  //step 2. 处理+-运算符
  Node finalNode = all_nodes[0];
  // cout << "finalNode: " << finalNode << endl;
  // cout << endl;
  size_t node_index = 0;
  for (size_t oper_index = 0; oper_index != opers.size(); ++oper_index) {
    node_index = oper_index + 1;
    if (opers[oper_index] == "+") {
      // cout << "finalNode: " << finalNode << endl;
      // cout << "all_nodes[node_index + 1]: " << all_nodes[node_index] << endl;
      finalNode = finalNode + all_nodes[node_index];
      // cout << "finalNode: " << finalNode << endl;
    }
    if (opers[oper_index] == "-") {
      finalNode = finalNode - all_nodes[node_index];
      // cout << "finalNode: " << finalNode << endl;
    }
  }

  return finalNode;
}

// log configuration
DEFINE_int32(max_log_files, 3,
             "Maximum number of log files to retain per severity "
             "level. The most recent log files are retained. If set to 0, all "
             "log files are retained.");

int main(int argc, char* argv[]) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  base::InitGlogSafe(argv[0], false);
  string input;
  getline(cin, input);

  queue<string> expression;
  expression = StringUtil::SplitNumAndSign(input);

  Node node = buildExpression(expression);

  cout << node.rep() << " = " << node.calculate() << endl;
  LOG(ERROR) << node.rep() << " = " << node.calculate();

  base::ShutdownGlogSafe();
  return 0;
}