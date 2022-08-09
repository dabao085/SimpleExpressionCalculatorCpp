#ifndef _EXP_CAL_BINARY_NODE_H_
#define _EXP_CAL_BINARY_NODE_H_

#include "Node.h"

// enum CALTYPE
// {
//     ADD,
//     MINUS,
//     MULTIPLY,
//     DIVIDE
// };

class BinaryNode : public NodeBase {
  protected:// have to be protected?
  BinaryNode(const Node& lhs, const Node& rhs, const std::string& oper)
      : lhs_(lhs), rhs_(rhs), oper_(oper) {}
  std::string rep() const override {
    return lhs_.rep() + " " + oper_ + " " + rhs_.rep();
  }

  std::string oper_;// 记录操作类型
  Node lhs_, rhs_;  // 记录运算符两侧的节点
};

class AddNode : public BinaryNode {
  friend Node operator+(const Node&, const Node&);
  AddNode(const Node& lhs, const Node& rhs) : BinaryNode(lhs, rhs, "+") {}
  double calculate() const override {
    return lhs_.caculate() + rhs_.caculate();
  }
};

class DeleteNode : public BinaryNode {
  friend Node operator-(const Node&, const Node&);
  DeleteNode(const Node& lhs, const Node& rhs) : BinaryNode(lhs, rhs, "-") {}
  double calculate() const override {
    return lhs_.caculate() - rhs_.caculate();
  }
};

class MultiplyNode : public BinaryNode {
  friend Node operator*(const Node&, const Node&);
  MultiplyNode(const Node& lhs, const Node& rhs) : BinaryNode(lhs, rhs, "*") {}
  double calculate() const override {
    return lhs_.caculate() * rhs_.caculate();
  }
};

class DivideNode : public BinaryNode {
  friend Node operator/(const Node&, const Node&);
  DivideNode(const Node& lhs, const Node& rhs) : BinaryNode(lhs, rhs, "/") {}
  double calculate() const override {
    return lhs_.caculate() / rhs_.caculate();
  }
};

#endif