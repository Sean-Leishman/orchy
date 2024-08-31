#pragma once

#include <any>
#include <string>

enum TokenType : int {
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

class Token {
private:
  const TokenType type;
  const std::string lexeme;
  const int line;
  const std::any literal;

public:
  Token(TokenType, std::string, std::any, int);
  std::string to_string() const {
    return std::to_string(type) + " " + lexeme + " ";
  };

  std::string Lexeme() { return lexeme; }
};

std::ostream &operator<<(std::ostream &out, const Token &token);
