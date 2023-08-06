#pragma once

#include "token/token.hpp"

#include <string>
#include <vector>

class Scanner
{
  private:
  const std::string source;

  std::vector<Token> tokens;

  int start = 0;
  int current = 0;
  int line = 1;

  bool is_at_end() { return current >= source.length(); }
  void scan_token();

  char next_char() { return source.at(current++); };
  void add_token(TokenType type) { add_token(type, nullptr); }
  void add_token(TokenType type, void* literal);

  public:
  Scanner();
  Scanner(std::string);
  ~Scanner() {}

  std::vector<Token> scan_tokens();
};