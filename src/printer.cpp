#include <printer.hpp>
#include <vector>

std::string AstPrinter::visit_binary_expression(Binary expr) {
  return parenthesize(expr.op.Lexeme(), std::vector{expr.left, expr.right});
}

std::string AstPrinter::visit_grouping_expression(Grouping expr) {
  return parenthesize("group", std::vector{expr.expression});
}

std::string AstPrinter::visit_literal_expression(Literal expr) {
  return "nil"; // should be expr.ToString()
}

std::string AstPrinter::visit_unary_expression(Unary expr) {
  return parenthesize(expr.op.Lexeme(), std::vector{expr.right});
}

std::string AstPrinter::parenthesize(std::string name,
                                     std::vector<Expression> exprs) {
  std::string result = "(" + name;
  for (auto expr : exprs) {
    result += " ";
    result += expr.accept(this);
  }
  result += ")";
  return result;
}

std::string AstPrinter::print(Expression expr) { return expr.accept(this); }
