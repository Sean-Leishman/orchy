# Setup

## Prerequisites

- CMake 3.10 or newer.
- A C++17 compiler. The CMake preset hard-codes `/usr/bin/clang` and
  `/usr/bin/clang++`; on systems without those exact paths, either
  install Clang there, edit `CMakePresets.json`, or use the plain
  `cmake -B build` flow below.
- Ninja (only required if you use the preset).
- Optional: `clangd` and `clang-format` to honour the checked-in
  `.clangd` and `cpp/.clang-format`.

The repo targets Linux. It was last built on WSL2; macOS should also work
if the compiler paths are adjusted. There is no Windows support beyond
WSL.

## Build (plain CMake)

This matches `run.sh`:

```
cmake -B build -S . -DCMAKE_EXPORT_COMPILE_COMMANDS=1
cmake --build build
```

Artefacts:

- `build/apps/app` - the interpreter front-end
- `build/src/liblexer_lib.a` - the scanner/AST library
- `build/tools/ast_generator` - the AST header generator

`compile_commands.json` is exported into `build/` for `clangd`.

## Build (CMake preset)

```
cmake --preset x64-clang-linux-debug
cmake --build --preset linux-debug
```

Output goes to `out/build/x64-clang-linux-debug/` instead of `build/`.

## Run

REPL:

```
./build/apps/app
> 1 + 2
token: 8 1
token: 7 +
token: 10 2
token: 49
```

(The numbers are `TokenType` enum values; today the binary only scans and
prints tokens.)

Run a script file:

```
./build/apps/app path/to/source.lox
```

`run_file` resolves the path relative to the current working directory
(`std::filesystem::current_path() / filename`).

## Regenerating expression.hpp

```
./build/tools/ast_generator include/
```

Note: the checked-in `include/expression.hpp` has been edited beyond what
the generator emits (it uses `std::unique_ptr` and `std::any`). Running
the generator will overwrite those edits - prefer hand-editing for now.

## Cleaning

```
rm -rf build out
```

Both directories are gitignored (`build/`, `.cache/`); `out/` is created
only when using the preset.

## Editor / tooling

- `.clangd` at the repo root keeps `clangd` happy with the layout.
- `cpp/.clang-format` holds the formatting rules; format with
  `clang-format -i <files>`.
- `cpp/.vscode/` contains VS Code workspace settings.

## Troubleshooting

- *"Could not find compiler"* with the preset: the preset hard-codes
  `/usr/bin/clang`. Either install Clang there or drop the preset.
- *Linker errors involving `Visitor`*: `Visitor`'s destructor is declared
  pure-virtual but no definition is checked in here; if a future change
  triggers a link failure, add an empty `Visitor::~Visitor() {}` in
  `src/expression.cpp`.
- *`parser.cpp` not found / empty target*: `parser.cpp` is intentionally
  empty and not listed in `src/CMakeLists.txt`. Do not add it to the
  source list until it has real content.
