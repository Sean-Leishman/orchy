#pragma once

#include <string>

enum TokenType : int
{
  LEFT_PAREN,
  RIGHT_PAREN,
  LEFT_BRACE,
  RIGHT_BRACE,
  COMMA,
  DOT,
  MINUS,
  PLUS,
  SEMICOLON,
  SLASH,
  STAR,

  BANG,
  BANG_EQUAL,
  EQUAL,
  EQUAL_EQUAL,
  GREATER,
  GREATER_EQUAL,
  LESS,
  LESS_EQUAL,

  IDENTIFIER,
  STRING,
  NUMBER,

  AND,
  CLASS,
  ELSE,
  FALSE,
  FUN,
  FOR,
  IF,
  NIL,
  OR,
  PRINT,
  RETURN,
  SUPER,
  THIS,
  TRUE,
  VAR,
  WHILE,

  END_OF_FILE,
};

class TokenInterface
{
  public:
  std::string to_string();

  private:
};

template <typename T>
class Token : TokenInterface
{
  private:
  const TokenType type;
  const std::string lexeme;
  const T literal;
  const int line;

  public:
  Token(TokenType, std::string, T, int);
  std::string to_string() const
  {
    return std::to_string(type) + " " + lexeme + " ";
  };
};

template <typename T>
std::ostream& operator<<(std::ostream& out, Token<T> const& token);
