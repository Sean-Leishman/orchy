#pragma once
#include "token.hpp"
#include <memory>
class Binary;
class Grouping;
class Literal;
class Unary;
class Visitor {
public:
  virtual ~Visitor() = 0;
  virtual std::any visit_binary_expression(Binary &) = 0;
  virtual std::any visit_grouping_expression(Grouping &) = 0;
  virtual std::any visit_literal_expression(Literal &) = 0;
  virtual std::any visit_unary_expression(Unary &) = 0;
};
class Expression {
public:
  virtual ~Expression() = 0;
  virtual std::any accept(Visitor *visitor);
};

class Unary : public Expression {
public:
  Unary(Token op, std::unique_ptr<Expression> right);

  Token op;
  std::unique_ptr<Expression> right_;
  std::any accept(Visitor *visitor) override;
};
class Binary : public Expression {
public:
  Binary(std::unique_ptr<Expression> left, Token op,
         std::unique_ptr<Expression> right);
  ~Binary();

  std::unique_ptr<Expression> left_;
  Token op;
  std::unique_ptr<Expression> right_;
  std::any accept(Visitor *visitor) override;
};
class Grouping : public Expression {
public:
  Grouping(std::unique_ptr<Expression> expression);
  ~Grouping();

  std::unique_ptr<Expression> expression_;
  std::any accept(Visitor *visitor) override;
};
class Literal : public Expression {
public:
  Literal(std::any value);
  ~Literal();

  std::any value;
  std::any accept(Visitor *visitor) override;
};
