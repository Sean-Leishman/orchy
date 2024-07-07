#include <printer.hpp>

std::string AstPrinter::visit_binary_expression(Binary expr) {
  return parenthesize(expr.op, expr.left, expr.right);
}

std::string AstPrinter::visit_grouping_expression(Grouping expr) {
  return parenthesize("group", expr.expression);
}

std::string AstPrinter::visit_literal_expression(Literal expr) {
  if (expr.value == nullptr)
    return "nil";
  return expr.value->to_string();
}

std::string AstPrinter::visit_unary_expression(Unary expr) {
  return parenthesize(expr.op, expr.right);
}

std::string parenthesize(std::string name, std::vector<Expression> exprs) {
  std::string result = "(" + name;
  for (auto expr : exprs) {
    result += " ";
    result += expr.accept(*this);
  }
  result += ")";
  return result;
}

std::string AstPrinter::print(Expression expr) { return expr.accept(*this); }
