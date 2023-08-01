#include "lexer/lexer.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
  auto lox = Lox();

  if (argc > 2)
  {
    std::cout << "Usage: cpplox [script]";
  }
  else if (argc == 2)
  {
    lox.run_file(argv[1]);
  }
  else
  {
    // lox.run_prompt();
  }
  return 0;
}