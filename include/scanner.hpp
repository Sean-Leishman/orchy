#pragma once

#include "token.hpp"

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class Scanner {
private:
  const std::string source;
  std::unordered_map<std::string, TokenType> keywords;

  std::vector<Token> tokens;

  int start = 0;
  int current = 1;
  int line = 0;

  bool is_at_end() { return current >= source.size(); }
  bool match(char c);

  void scan_token();

  char next_char() { return source.at(current++); };
  char peek();
  char peek(int);

  void handle_string();
  void handle_number();
  void handle_identifier();
  void handle_multi_line_comment();

  void add_token(TokenType type) { add_token(type, {}); }
  void add_token(TokenType type, std::any literal);

public:
  Scanner();
  Scanner(std::string);
  ~Scanner() {}

  std::vector<Token> scan_tokens();
};
