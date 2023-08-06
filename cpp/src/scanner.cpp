#include "scanner/scanner.hpp"
#include "lexer/lexer.hpp"
#include "token/token.hpp"

#include <vector>

Scanner::Scanner() : source(""){};
Scanner::Scanner(std::string source_string) : source{source_string}
{
  std::cout << "Yes: " << source;
};

void Scanner::scan_token()
{
  char c = next_char();
  switch (c)
  {
    case '(':
      add_token(LEFT_PAREN);
      break;
    case ')':
      add_token(RIGHT_PAREN);
      break;
    case '{':
      add_token(LEFT_BRACE);
      break;
    case '}':
      add_token(RIGHT_PAREN);
      break;
    case ',':
      add_token(COMMA);
      break;
    case '.':
      add_token(DOT);
      break;
    case '-':
      add_token(MINUS);
      break;
    case '+':
      add_token(PLUS);
      break;
    case ';':
      add_token(SEMICOLON);
      break;
    case '*':
      add_token(STAR);
      break;
    default:
      Lox::error(line, std::string("Unexpected character ") + c);
      break;
  }
};

void Scanner::add_token(TokenType type, void* literal)
{
  std::string text = source.substr(start, current);
  tokens.push_back(Token(type, text, literal, line));
}

std::vector<Token> Scanner::scan_tokens()
{
  std::cout << "Yes";
  while (!is_at_end())
  {
    start = current;
    scan_token();
  }

  Token token(END_OF_FILE, "", nullptr, line);
  tokens.push_back(token);

  return tokens;
};
