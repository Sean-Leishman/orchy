#pragma once

#include <iostream>
#include <string>

class Lox
{
  public:
  Lox(){};
  ~Lox(){};

  int run_file(char*);
  void run_prompt();
  int run(std::string&);
  static void error(int line, std::string message);

  private:
  bool hasError = false;
  static void report(int line, std::string where, std::string message);
};

namespace
{
inline std::string substring(std::string string, int a, int b)
{
  if (a > b)
  {
    return string;
  }
  return string.substr(a, b - a);
}
} // namespace