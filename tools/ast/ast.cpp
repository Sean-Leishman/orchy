#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::string ToLower(std::string str) {
  for (auto &ch : str) {
    ch = tolower(ch);
  }
  return str;
}

std::vector<std::string> split(std::string str, char delimiter) {
  std::vector<std::string> s{};
  std::string curr = {};

  for (auto &ch : str) {
    if (ch == delimiter) {
      s.push_back(curr);
      curr = {};
    } else {
      curr += ch;
    }
  }
  s.push_back(curr);
  return s;
}

void define_type(std::ofstream &fs, std::string &base_name,
                 std::string &class_name, std::string &field_list) {
  fs << "class " + class_name + " : public " + base_name + "{\npublic:\n";

  std::string input;
  std::vector<std::string> fields = split(field_list, ',');
  for (auto &field : fields) {
    std::string type = split(field, ' ').at(0);
    std::string name = split(field, ' ').at(1);
    input += type + " " + name + ";";
  }
  fs << input;

  fs << class_name + "(";

  input = {};
  for (auto &field : fields) {
    std::string type = split(field, ' ').at(0);
    std::string name = split(field, ' ').at(1);
    input += type + " " + name + ",";
  }
  fs << input.substr(0, input.size() - 1);
  fs << ") :";

  input = {};
  for (auto &field : fields) {
    std::string s = split(field, ' ').at(1);
    input += s + "(" + s + "),";
  }
  fs << input.substr(0, input.size() - 1);
  fs << "{}";

  fs << "template <typename T> T accept(Visitor<T> * visitor) { "
     << "return visitor->visit_" + ToLower(class_name) + "_" +
            ToLower(base_name) + "(this);}";
  fs << "};";
}

void define_visitor(std::ofstream &fs, std::string &class_name,
                    std::vector<const char *> types) {
  fs << "template <typename T> class Visitor { public:";
  class_name[0] = tolower(class_name[0]);

  for (auto &type : types) {
    std::string t = std::string(type);
    int split_position = t.find(':');

    std::string type_name = t.substr(0, split_position);
    type_name[0] = tolower(type_name[0]);

    fs << "virtual T visit_" + type_name + "_" + class_name + "(";

    type_name[0] = toupper(type_name[0]);
    fs << type_name + ");";
  }
  fs << "};";
}

void define_ast(std::string output_dir, std::string base_name,
                std::vector<const char *> types) {
  base_name[0] = tolower(base_name[0]);
  std::string output_path = output_dir + "/" + base_name + ".hpp";
  base_name[0] = toupper(base_name[0]);

  std::ofstream fs;
  fs.open(output_path, std::ios::trunc);

  fs << "#pragma once\n";
  fs << "#include \"token.hpp\"\n";
  for (const char *type : types) {
    int split_position = std::string(type).find(':');
    std::string name = std::string(type).substr(0, split_position);

    fs << "class " << name << ";\n";
  }

  define_visitor(fs, base_name, types);
  base_name[0] = toupper(base_name[0]);

  fs << "class " + base_name + "{public:\n";
  fs << "template <typename T> T accept(Visitor<T>* visitor);";
  fs << "};";

  for (const char *type : types) {
    std::string str_type = std::string(type);
    int split_position = str_type.find(':');

    std::string class_name = str_type.substr(0, split_position);
    std::string fields =
        str_type.substr(split_position + 1, str_type.size() - split_position);
    define_type(fs, base_name, class_name, fields);
  }

  fs.close();
}

int main(int argc, char **argv) {
  if (argc > 2) {
    std::cout << "Usage: cpplox [output directory]\n";
    return -1;
  } else if (argc == 2) {
    std::string output_dir = argv[1];
    define_ast(output_dir, "Expression",
               std::vector{"Binary:Expression left,Token op,Expression right",
                           "Grouping:Expression expression",
                           "Literal:std::any value",
                           "Unary:Token op,Expression right"});
    return 0;
  } else {
    std::cout << "Usage: cpplox [script]\n";
    return -1;
  }
}
