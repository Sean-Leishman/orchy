#include "token.hpp"

#include <ostream>

Token::Token(TokenType type, std::string text, std::any literal, int line)
    : type{type}, lexeme{text}, literal{literal}, line{line}
{
}

std::ostream& operator<<(std::ostream& out, Token const& token)
{
  out << token.to_string();
  return out;
}
