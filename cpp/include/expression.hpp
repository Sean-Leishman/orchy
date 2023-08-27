#include "token.hpp"

struct Expression
{
};

struct Binary : Expression
{
  Expression left;
  Token op;
  Expression right;
};

struct Unary : Expression
{
  Token op;
  Expression expr;
};
