#ifndef _EXP_CAL_NODE_H_
#define _EXP_CAL_NODE_H_

#include "StringUtil.h"
#include <memory>
#include <stdio.h>

class NodeBase {
  friend class Node;

public:
  NodeBase() = default;
  virtual ~NodeBase() = default;

private:
  virtual double calculate() const = 0;
  virtual std::string rep() const = 0;
};

class NumberNode : public NodeBase {
  friend class Node;

private:// have to be private?
  NumberNode(double value) : value_(value) {}
  double calculate() const override { return value_; }
  std::string rep() const override {//return std::to_string(value_);
    std::string result(std::to_string(value_));
    StringUtil::rtrimChar(result, '0');
    StringUtil::rtrimChar(result, '.');
    return result;
  }

private:
  double value_;
};

typedef struct Result_ {
  double result_;
} Result;

// 描述node的结构体, node默认采用double类型。
class Node {
  friend Node operator+(const Node&, const Node&);
  friend Node operator-(const Node&, const Node&);
  friend Node operator*(const Node&, const Node&);
  friend Node operator/(const Node&, const Node&);

public:
  Node(double value) : node_(new NumberNode(value)) {}
  double caculate() const { return node_->calculate(); }
  std::string rep() const { return node_->rep(); }

private:
  Node(std::shared_ptr<NodeBase> node) : node_(node) {}
  std::shared_ptr<NodeBase> node_;
};

#endif