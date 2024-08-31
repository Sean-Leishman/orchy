#pragma once
#include "token.hpp"
class Binary;
class Grouping;
class Literal;
class Unary;
template <typename T> class Visitor {
public:
  virtual T visit_binary_expression(Binary);
  virtual T visit_grouping_expression(Grouping);
  virtual T visit_literal_expression(Literal);
  virtual T visit_unary_expression(Unary);
};
class Expression {
public:
  template <typename T> T accept(Visitor<T> *visitor);
};
class Binary : public Expression {
public:
  Expression left;
  Token op;
  Expression right;
  Binary(Expression left, Token op, Expression right)
      : left(left), op(op), right(right) {}
  template <typename T> T accept(Visitor<T> *visitor) {
    return visitor->visit_binary_expression(this);
  }
};
class Grouping : public Expression {
public:
  Expression expression;
  Grouping(Expression expression) : expression(expression) {}
  template <typename T> T accept(Visitor<T> *visitor) {
    return visitor->visit_grouping_expression(this);
  }
};
class Literal : public Expression {
public:
  std::any value;
  Literal(std::any value) : value(value) {}
  template <typename T> T accept(Visitor<T> *visitor) {
    return visitor->visit_literal_expression(this);
  }
};
class Unary : public Expression {
public:
  Token op;
  Expression right;
  Unary(Token op, Expression right) : op(op), right(right) {}
  template <typename T> T accept(Visitor<T> *visitor) {
    return visitor->visit_unary_expression(this);
  }
};
