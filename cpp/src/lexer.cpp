#include "lexer/lexer.hpp"
#include "scanner/scanner.hpp"
#include "token/token.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <filesystem>

int Lox::run_file(char* filename)
{
  std::filesystem::path filepath = std::filesystem::current_path() / filename;
  std::ifstream file{filepath, std::fstream::binary | std::fstream::ate};
  if (!file.is_open())
  {
    std::cerr << "Failed to open file: " << filepath << std::endl;
    return 1;
  }

  int size = file.tellg();

  file.seekg(0);

  std::vector<char> buffer(size);
  if (!file.read(buffer.data(), size))
  {
    std::cerr << "Failed to read file" << std::endl;
    file.close();
    return 1;
  }

  file.close();

  std::string string{buffer.begin(), buffer.end()};

  run(string);
  return 0;
};

int Lox::run(std::string& source)
{
  Scanner scanner(source);

  std::vector<Token> tokens = scanner.scan_tokens();

  for (Token token : tokens)
  {
    std::cout << "token: " << token << "\n";
  }
}

void Lox::run_prompt()
{
  std::string buffer;
  for (;;)
  {
    std::cout << "> ";

    std::getline(std::cin, buffer);
    run(buffer);

    buffer.clear();
  }
}

void Lox::error(int line, std::string message) { report(line, "", message); }

void Lox::report(int line, std::string where, std::string message)
{
  printf("[line %i] Error %s: %s\n", line, where.c_str(), message.c_str());
}
