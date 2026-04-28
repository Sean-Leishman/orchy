# Notes

Loose observations from reading the tree. Not authoritative - flag anything
that contradicts the actual code.

## Status

- Last commit on `master`: `4e1eef1 Update up to final linking with std::any`,
  August 2024.
- The project is paused somewhere between *Crafting Interpreters* chapter 5
  ("Representing Code") and chapter 6 ("Parsing Expressions").
- Working tree is clean.

## Things that look intentional

- `std::any` instead of templated visitors. Commit `5329b44` explicitly
  switched away from templating Token literals; `120cf0b` and `4e1eef1`
  followed up by threading `std::any` through the visitor return type.
- `unique_ptr<Expression>` ownership for children. This is a deliberate
  divergence from the book (which uses Java references) and makes the AST
  destruct cleanly without manual delete.
- A standalone `ast_generator` tool rather than a build-time codegen step.
  It is not wired into the main build, which keeps `lexer_lib` self-
  contained.

## Things that look like bugs / leftovers

- `Scanner::current = 1;` initial value (in `scanner.hpp`) - every other
  index starts at 0. Worth re-checking against the book before "fixing".
- `case '}':` in `Scanner::scan_token` adds `RIGHT_PAREN` instead of
  `RIGHT_BRACE`. Almost certainly a copy-paste bug.
- `AstPrinter::visit_literal_expression` returns the literal string `"nil"`
  with a `// should be expr.ToString()` comment - placeholder.
- `Lox::run_file` prints a hard-coded `Binary(Literal(1), +, Literal(2))`
  through `AstPrinter` before doing anything with the file argument. Looks
  like leftover demo code from when the printer was added.
- `tools/ast/ast.hpp` is a 0-byte file.
- `src/parser.cpp` is a 0-byte file (also not in the build).
- `Token::to_string` formats `type` as a number, not the enum name; fine
  for debugging but noisy.
- `Scanner::handle_multi_line_comment` uses
  `peek() != '*' && peek(2) != '/'` - the `&&` should arguably be `||`
  to actually require both characters to match. Re-read carefully.

## Open questions

- Was the AST `Visitor` destructor's missing definition causing the
  "final linking" pain referenced in commit `4e1eef1`? If so, where did
  it land? I did not find a body for it in the current tree.
- Is `tools/ast/ast.cpp`'s output ever expected to compile as-is? It
  generates raw `Expression`/`Token` field types, not pointer or `any`
  forms - so it diverges from what `expression.hpp` actually uses now.
- Multi-character lookahead in `Scanner::peek(int)` is `1`-indexed
  (`current + n - 1`). Callers pass `2`. Consistent but easy to misuse.

## Worth doing next (if picking this up)

1. Implement chapter 6's recursive-descent parser into `src/parser.cpp`,
   add it to `src/CMakeLists.txt`, and have `Lox::run` call it.
2. Remove the demo `Binary` print from `Lox::run_file`.
3. Fix the `}` -> `RIGHT_BRACE` token bug.
4. Decide whether to keep `ast_generator` (and update it to emit the
   `unique_ptr`/`std::any` shape) or delete it and edit headers by hand.
5. Add a tiny test harness - even a fixed input file diffed against a
   golden token dump would catch regressions.
