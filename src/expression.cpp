#include "expression.hpp"

Unary::Unary(Token op, std::unique_ptr<Expression> right)
    : op(op), right_(std::move(right)) {}

std::any Unary::accept(Visitor *visitor) {
  return visitor->visit_unary_expression(*this);
}
Binary::Binary(std::unique_ptr<Expression> left, Token op,
               std::unique_ptr<Expression> right)
    : left_(std::move(left)), op(op), right_(std::move(right)) {}
Binary::~Binary() {}

std::any Binary::accept(Visitor *visitor) {
  return visitor->visit_binary_expression(*this);
}

Grouping::Grouping(std::unique_ptr<Expression> expression)
    : expression_(std::move(expression)) {}
Grouping::~Grouping() {}
std::any Grouping::accept(Visitor *visitor) {
  return visitor->visit_grouping_expression(*this);
}

Literal::Literal(std::any value) : value(value) {}
Literal::~Literal() {}
std::any Literal::accept(Visitor *visitor) {
  return visitor->visit_literal_expression(*this);
}
