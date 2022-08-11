#ifndef _EXP_CAL_BINARY_NODE_H_
#define _EXP_CAL_BINARY_NODE_H_

#include "node.h"

// enum CALTYPE
// {
//     ADD,
//     MINUS,
//     MULTIPLY,
//     DIVIDE
// };

class BinaryNode : public NodeBase {
protected: // have to be protected?
  BinaryNode(const Node& lhs, const Node& rhs, const std::string& oper)
      : lhs_(lhs), rhs_(rhs), oper_(oper) {}
  std::string rep() const override {
    return lhs_.rep() + " " + oper_ + " " + rhs_.rep();
  }

  Node lhs_;         // 记录运算符左侧的节点
  Node rhs_;         // 记录运算符右侧的节点
  std::string oper_; // 记录操作类型
};

class AddNode : public BinaryNode {
  friend Node operator+(const Node&, const Node&);
  AddNode(const Node& lhs, const Node& rhs) : BinaryNode(lhs, rhs, "+") {}
  double calculate() const override {
    return lhs_.calculate() + rhs_.calculate();
  }
};

class DeleteNode : public BinaryNode {
  friend Node operator-(const Node&, const Node&);
  DeleteNode(const Node& lhs, const Node& rhs) : BinaryNode(lhs, rhs, "-") {}
  double calculate() const override {
    return lhs_.calculate() - rhs_.calculate();
  }
};

class MultiplyNode : public BinaryNode {
  friend Node operator*(const Node&, const Node&);
  MultiplyNode(const Node& lhs, const Node& rhs) : BinaryNode(lhs, rhs, "*") {}
  double calculate() const override {
    return lhs_.calculate() * rhs_.calculate();
  }
};

class DivideNode : public BinaryNode {
  friend Node operator/(const Node&, const Node&);
  DivideNode(const Node& lhs, const Node& rhs) : BinaryNode(lhs, rhs, "/") {}
  double calculate() const override {
    return lhs_.calculate() / rhs_.calculate();
  }
};

#endif