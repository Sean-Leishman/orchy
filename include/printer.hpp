#include "expression.hpp"

#include <vector>

class AstPrinter : public Visitor {
public:
  AstPrinter(){};
  ~AstPrinter() override;

  std::string print(Binary &expr);

  std::any visit_binary_expression(Binary &expr) override;

  std::any visit_grouping_expression(Grouping &expr) override;

  std::any visit_literal_expression(Literal &expr) override;

  std::any visit_unary_expression(Unary &expr) override;

private:
  std::any parenthesize(std::string name, std::vector<Expression *> exprs);
};
