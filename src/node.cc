#include "node.h"
#include "binary_node.h"
using namespace std;

// ostream& operator<<(ostream& os, const Node& node)
// {
//     return os << node.rep();
// }

Node operator+(const Node& lhs, const Node& rhs) {
  return std::shared_ptr<NodeBase>(new AddNode(lhs, rhs));
}

Node operator-(const Node& lhs, const Node& rhs) {
  return std::shared_ptr<NodeBase>(new DeleteNode(lhs, rhs));
}

Node operator*(const Node& lhs, const Node& rhs) {
  return std::shared_ptr<NodeBase>(new MultiplyNode(lhs, rhs));
}

Node operator/(const Node& lhs, const Node& rhs) {
  return std::shared_ptr<NodeBase>(new DivideNode(lhs, rhs));
}