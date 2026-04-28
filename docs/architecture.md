# Architecture

orchy is structured as a small C++ codebase that mirrors the layout in
*Crafting Interpreters*: a `Lox` driver that owns the read/scan/(parse)/run
pipeline, with each stage broken into its own translation unit.

## Layout

```
.
|- apps/        executable entry point (apps/app.cpp -> `app`)
|- include/     public headers consumed by the lexer_lib target
|- src/         lexer_lib implementation files
|- tools/       host-side helpers built as separate executables
|   `- ast/     ast_generator - emits expression.hpp from a spec list
|- build/       cmake out-of-tree build dir (ignored)
|- run.sh       configure + build shortcut
|- CMakeLists.txt, CMakePresets.json
```

## Build graph

Root `CMakeLists.txt` declares the project and adds three subdirectories:

- `tools/` produces `ast_generator` (C++20) - a standalone tool that
  generates an AST header file. It is not linked into the runtime.
- `src/` produces `lexer_lib` (C++17), a static library compiled from
  `lexer.cpp`, `scanner.cpp`, `token.cpp`, `printer.cpp`, `expression.cpp`.
  Public include directory is `${PROJECT_SOURCE_DIR}/include`.
- `apps/` produces the `app` executable, linked against `lexer_lib`.

`parser.cpp` exists in `src/` but is empty and is *not* listed in
`src/CMakeLists.txt`'s `target_sources`, so it does not contribute to the
build today.

## Runtime pipeline

```
main(argc, argv)              apps/app.cpp
   |
   +-> Lox::run_prompt()      REPL loop, getline -> run(line)
   |
   +-> Lox::run_file(path)    reads file into a string -> run(string)
                              (also: prints a hard-coded demo Binary
                               expression through AstPrinter)
   |
   v
Lox::run(source)              src/lexer.cpp
   |
   v
Scanner(source).scan_tokens() src/scanner.cpp
   |
   v
std::vector<Token>            printed to stdout
```

Today the pipeline stops at the token vector - there is no parser stage
producing an `Expression` tree from real input. The `Expression` /
`AstPrinter` machinery only exercises hand-built trees.

## Lexer / scanner

- `Scanner` holds the immutable `source` string, a `keywords` map seeded in
  the constructor, plus three indices: `start`, `current`, `line`.
- `scan_tokens()` loops `scan_token()` until end-of-source, then appends an
  `END_OF_FILE` token.
- `scan_token()` is a `switch` over the next character, with helpers for
  strings, numbers, identifiers, and `/* ... */` style multi-line comments.
- One-line `//` comments are handled inline by consuming until newline.

`Token` is an immutable value type holding `TokenType`, lexeme string,
`std::any` literal, and source line.

## Expression AST

`include/expression.hpp` declares an abstract `Expression` plus four leaf
classes - `Unary`, `Binary`, `Grouping`, `Literal` - and a `Visitor`
interface with one `visit_*_expression` per leaf. Each leaf overrides
`accept(Visitor*)` to dispatch to the matching visitor method.

Children are owned via `std::unique_ptr<Expression>`. Visitor methods
return `std::any`; `AstPrinter::print` `any_cast`s to `std::string`.

`AstPrinter` formats the tree using a private `parenthesize(name, exprs)`
helper - canonical *Crafting Interpreters* style.

## AST generator

`tools/ast/ast.cpp` is a separate `ast_generator` executable. It accepts a
single output-directory argument and writes an `expression.hpp` derived
from a hard-coded spec list of `Name:fields` strings. It is not invoked by
the main build - the checked-in `include/expression.hpp` was hand-edited
after generation (the file uses `std::any` and `unique_ptr`, which the
generator does not emit verbatim).

## What is missing

- Parser: `src/parser.cpp` is empty.
- Interpreter: no evaluator visitor.
- Statements / environments / functions / classes - the chapters past
  expressions are not started.
- Tests, CI, packaging.
