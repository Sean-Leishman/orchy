#include "lexer/lexer.hpp"

#include <fstream>
#include <iostream>
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
  std::cout << size << std::endl;

  file.seekg(0);

  std::vector<char> buffer(size);
  if (!file.read(buffer.data(), size))
  {
    std::cerr << "Failed to read file" << std::endl;
    file.close();
    return 1;
  }

  file.close();

  std::stringstream source;
  source.rdbuf()->pubsetbuf(buffer.data(), size);

  run(source);
  return 0;
};

int Lox::run(std::stringstream& source)
{
  char ch;
  while (source.get(ch))
  {
    std::cout << ch << std::endl;
  }
}
