#include "constants.h"

#include "lexer.hpp"
#include "scanner.hpp"
#include "token.hpp"

#include <cctype>
#include <stdexcept>
#include <string>
#include <vector>

Scanner::Scanner() : source(""){};
Scanner::Scanner(std::string source_string) : source{source_string}
{
  keywords.insert({"and", AND});
  keywords.insert({"or", OR});
  keywords.insert({"class", CLASS});
  keywords.insert({"false", FALSE});
  keywords.insert({"for", FOR});
  keywords.insert({"fun", FUN});
  keywords.insert({"if", IF});
  keywords.insert({"nil", NIL});
  keywords.insert({"print", PRINT});
  keywords.insert({"return", RETURN});
  keywords.insert({"super", SUPER});
  keywords.insert({"this", THIS});
  keywords.insert({"true", TRUE});
  keywords.insert({"var", VAR});
  keywords.insert({"while", WHILE});
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
    case '!':
      add_token(match('=') ? BANG_EQUAL : BANG);
      break;
    case '=':
      add_token(match('=') ? EQUAL_EQUAL : EQUAL);
      break;
    case '<':
      add_token(match('=') ? LESS_EQUAL : LESS);
      break;
    case '>':
      add_token(match('=') ? GREATER_EQUAL : GREATER);
      break;
    case '/':
      if (match('/'))
      {
        // A comment goes until the end of the line.
        while (peek() != '\n' && !is_at_end())
          next_char();
      }
      else if (match('*'))
      {
        handle_multi_line_comment();
      }
      else
      {
        add_token(SLASH);
      }
      break;
    case ' ':
    case '\r':
    case '\t':
      break;
    case '\n':
      line++;
      break;
    case '"':
      handle_string();
      break;
    default:
      if (isdigit(c))
      {
        handle_number();
      }
      else if (isalpha(c) || c == '_')
      {
        handle_identifier();
      }
      else
      {
        Lox::error(line, std::string("Unexpected character ") + c);
      }
      break;
  }
};

void Scanner::handle_multi_line_comment()
{
  while (peek() != '*' && peek(2) != '/' && !is_at_end())
  {
    next_char();
  }
  if (is_at_end())
  {
    Lox::error(line, "Unterminated comment");
    return;
  }
  next_char();
  next_char();
}

void Scanner::handle_identifier()
{
  while (isalpha(peek()) || isdigit(peek()))
  {
    next_char();
  }
  std::string string = substring(source, start, current);
  try
  {
    TokenType type = keywords.at(string);
    add_token(type);
  }
  catch (std::out_of_range)
  {
    TokenType type = IDENTIFIER;
    add_token(type);
  }
}

void Scanner::handle_string()
{
  while (peek() != '"' && !is_at_end())
  {
    if (peek() == '\n')
    {
      line++;
    }
    next_char();
  }

  if (is_at_end())
  {
    Lox::error(line, "Unterminated string");
    return;
  }
  // Consume closing "
  next_char();

  // Strip ""
  std::string string{substring(source, start + 1, current - 1)};
  add_token(STRING, &string);
}

void Scanner::handle_number()
{
  while (isdigit(peek()))
  {
    next_char();
  }

  if (peek() == '.' && isdigit(peek(2)))
  {
    next_char();
    while (isdigit(peek()))
    {
      next_char();
    }
  }
  auto number = std::stod(substring(source, start, current));
  add_token(NUMBER, &number);
}

char Scanner::peek()
{
  if (is_at_end())
  {
    return '\0';
  }
  return source.at(current);
}

char Scanner::peek(int n)
{
  if (current + n - 1 >= source.length())
  {
    return '\0';
  }
  return source.at(current + n - 1);
}

bool Scanner::match(char expected)
{
  if (is_at_end())
  {
    return false;
  }
  if (source.at(current) != expected)
  {
    return false;
  }
  current++;
  return true;
}

void Scanner::add_token(TokenType type, void* literal)
{
  std::string text = substring(source, start, current);
  tokens.push_back(Token(type, text, literal, line));
}

std::vector<Token> Scanner::scan_tokens()
{
  while (!is_at_end())
  {
    start = current;
    scan_token();
  }

  Token token(END_OF_FILE, "", nullptr, line);
  tokens.push_back(token);

  return tokens;
};
