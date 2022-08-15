#include "base/logging.h"
#include "binary_node.h"
#include "gflags/gflags.h"
#include "node_util.h"
#include <iostream>

using namespace std;

//ostream& operator<<(ostream& os, const Node& node) { return os << node.rep(); }


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

  Node root_node = nodeutil::buildExpression(expression);

  cout << root_node.rep() << " = " << root_node.calculate() << endl;
  LOG(ERROR) << root_node.rep() << " = " << root_node.calculate();

  base::ShutdownGlogSafe();
  return 0;
}