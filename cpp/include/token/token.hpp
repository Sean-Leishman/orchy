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

class Token
{
  private:
  const TokenType type;
  const std::string lexeme;
  const void* literal;
  const int line;

  public:
  Token(TokenType, std::string, void*, int);
  std::string to_string() const { return type + " " + lexeme + " "; };
};

std::ostream& operator<<(std::ostream& out, Token const& token);