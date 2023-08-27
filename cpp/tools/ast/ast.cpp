#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> split(std::string str, char delimiter)
{
  std::vector<std::string> s{};
  std::string curr = {};

  for (auto& ch : str)
  {
    if (ch == delimiter)
    {
      s.push_back(curr);
      curr = {};
    }
    else
    {
      curr += ch;
    }
  }
  s.push_back(curr);
  return s;
}

void define_type(std::ofstream* fs, std::string& base_name,
                 std::string& class_name, std::string& field_list)
{
  *fs << "struct " + class_name + " : " + base_name + "{\n";

  std::vector<std::string> fields = split(field_list, ',');
  for (auto& field : fields)
  {
    std::string s = split(field, ' ').at(1);
    *fs << " " + field + ";";
  }

  *fs << "};";
}

void define_ast(std::string output_dir, std::string base_name,
                std::vector<const char*> types)
{
  std::string output_path = output_dir + "/" + base_name;

  std::ofstream fs;
  fs.open(output_path, std::ios::trunc);

  fs << "struct " + base_name + "{\n";
  for (const char* type : types)
  {
    std::string str_type = std::string(type);
    int split_position = str_type.find(':');

    std::string class_name = str_type.substr(0, split_position);
    std::string fields =
        str_type.substr(split_position + 1, str_type.size() - split_position);
    define_type(&fs, base_name, class_name, fields);
  }

  fs.close();
}

int main(int argc, char** argv)
{
  if (argc > 2)
  {
    std::cout << "Usage: cpplox [script]\n";
    return -1;
  }
  else if (argc == 2)
  {
    std::string output_dir = argv[1];
    define_ast(
        output_dir, "Expression",
        std::vector{"Binary:Expression left, Token operator, Expression right",
                    "Grouping:Expression expression", "Literal:Object value",
                    "Unary:Token operator, Expression right"});
    return 0;
  }
  else
  {
    std::cout << "Usage: cpplox [script]\n";
    return -1;
  }
}