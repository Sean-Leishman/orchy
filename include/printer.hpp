#include <expression.hpp>

#include <vector>

class AstPrinter : public Visitor<std::string> {
public:
  AstPrinter(){};
  ~AstPrinter(){};

  std::string print(Expression expr);

  std::string visit_binary_expression(Binary expr);

  std::string visit_grouping_expression(Grouping expr);

  std::string visit_literal_expression(Literal expr);

private:
  std::string parenthesize(std::string name, std::vector<Expression> exprs);
};
