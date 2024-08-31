#include "printer.hpp"
#include <any>
#include <vector>

AstPrinter::~AstPrinter() {}

std::any AstPrinter::visit_binary_expression(Binary &expr) {
  return parenthesize(expr.op.Lexeme(),
                      std::vector{expr.left_.get(), expr.right_.get()});
}

std::any AstPrinter::visit_grouping_expression(Grouping &expr) {
  return parenthesize("group", std::vector{expr.expression_.get()});
}

std::any AstPrinter::visit_literal_expression(Literal &expr) {
  return "nil"; // should be expr.ToString()
}

std::any AstPrinter::visit_unary_expression(Unary &expr) {
  return parenthesize(expr.op.Lexeme(), std::vector{expr.right_.get()});
}

std::any AstPrinter::parenthesize(std::string name,
                                  std::vector<Expression *> exprs) {
  std::string result = "(" + name;
  for (auto expr : exprs) {
    result += " ";
    result += std::any_cast<std::string>(expr->accept(this));
  }
  result += ")";
  return result;
}

std::string AstPrinter::print(Binary &expr) {
  return std::any_cast<std::string>(expr.accept(this));
}
