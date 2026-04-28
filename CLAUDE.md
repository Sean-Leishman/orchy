# orchy

## Purpose

A hobby implementation of the Lox tree-walking interpreter from Robert
Nystrom's *Crafting Interpreters*, written in C++17. The project is partway
through Part II of the book: a scanner producing tokens, an `Expression` AST
hierarchy with a visitor-based `AstPrinter`, and a small code generator for
those AST node classes. The parser is empty, so end-to-end source-to-AST
execution is not yet wired up.

## Tech stack

- C++17 (one tool subdirectory bumps to C++20)
- CMake >= 3.10, Ninja generator via CMakePresets
- Clang / Clang++ (paths hard-coded in `CMakePresets.json`)
- `.clangd` and `.clang-format` for editor tooling

## Key files / entry points

- `apps/app.cpp` - `main`, dispatches to `Lox::run_file` or `Lox::run_prompt`.
- `src/lexer.cpp`, `include/lexer.hpp` - the `Lox` driver class (file/REPL/run).
- `src/scanner.cpp`, `include/scanner.hpp` - character-by-character tokenizer,
  keyword table, string / number / identifier / multi-line comment handling.
- `include/token.hpp`, `src/token.cpp` - `TokenType` enum and `Token` value type.
- `include/expression.hpp`, `src/expression.cpp` - `Expression` base plus
  `Binary` / `Grouping` / `Literal` / `Unary` and a `Visitor` interface.
- `include/printer.hpp`, `src/printer.cpp` - `AstPrinter` visitor that
  parenthesizes an expression tree.
- `src/parser.cpp` - empty placeholder.
- `tools/ast/ast.cpp` - standalone `ast_generator` executable that emits an
  `expression.hpp`-shaped header from a type spec list.
- `CMakeLists.txt` (root, `apps/`, `src/`, `tools/`) - build wiring; `src/`
  produces the `lexer_lib` static library that `apps/app` links against.
- `run.sh` - one-shot configure-and-build helper.
- `include/constants.h` - small `ErrorCodes` enum.

## How to run / dev

From the repo root:

```
./run.sh                 # cmake -B build -S .  &&  cd build && make
./build/apps/app         # REPL
./build/apps/app <file>  # run a script (reads file, prints scanned tokens)
```

Or via the preset (writes to `out/build/x64-clang-linux-debug/`):

```
cmake --preset x64-clang-linux-debug
cmake --build --preset linux-debug
```

The AST generator is built as `ast_generator`; invoke it as
`ast_generator <output_dir>` to regenerate an `expression.hpp`.

## Conventions noticed

- Headers in `include/`, implementations in `src/`; one library
  (`lexer_lib`) consumes the whole `src/` tree.
- Mostly `snake_case` for functions/methods, `PascalCase` for classes and
  enum values (token types in `SCREAMING_SNAKE_CASE`).
- Visitor pattern via `std::any` returns rather than templated visitors.
- AST nodes own children through `std::unique_ptr<Expression>`.
- `.clang-format` is checked in - prefer formatting through it.
- Build artefacts (`build/`, `.cache/`) are gitignored.

## Gaps / honesty

- `src/parser.cpp` is empty; there is no parser yet, so `Lox::run` only
  scans and prints tokens.
- `tools/ast/ast.hpp` is empty; `ast.cpp` writes generated code directly.
- `Lox::run_file` hard-codes a demo `Binary` expression and prints it via
  `AstPrinter` before reading the file - leftover scaffolding.
- `Scanner::current` starts at 1 (not 0); not verified against the book.
- `Visitor`'s pure-virtual destructor is declared but I did not find a
  definition; linking has been observed to work per commit history but is
  not re-verified here.
- No tests, no CI, no license file. Last commit Aug 2024.
