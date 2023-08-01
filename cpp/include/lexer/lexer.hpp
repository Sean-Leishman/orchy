#pragma once

#include <iostream>

class Lox
{
  public:
  int run_file(char*);
  void run_prompt();
  int run(std::stringstream&);

  private:
};