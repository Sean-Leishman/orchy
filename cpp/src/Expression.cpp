#include "token.hpp"
class Binary;
class Grouping;
class Literal;
class Unary;
class Visitor;

class Expression
{
  std::any accept(Visitor<std::any>& visitor);
};
class Binary : public Expression
{
  Expression left;
  Token op;
  Expression right;
  Binary(Expression left, Token op, Expression right)
      : left(left), op(op), right(right)
  {
  }
};
class Grouping : public Expression
{
  Expression expression;
  Grouping(Expression expression) : expression(expression) {}
};
class Literal : public Expression
{
  Object value;
  Literal(Object value) : value(value) {}
};
class Unary : public Expression
{
  Token op;
  Expression right;
  Unary(Token op, Expression right) : op(op), right(right) {}
};
template <typename T>
class Visitor
{
  virtual T visitBinary_Expression(Binary);
  virtual T visitGrouping_Expression(Grouping);
  virtual T visitLiteral_Expression(Literal);
  virtual T visitUnary_Expression(Unary);
};
