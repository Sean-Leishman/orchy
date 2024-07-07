set(TARGET_NAME ast_generator)

add_executable(${TARGET_NAME} ast/ast.cpp ast/ast.hpp)

target_compile_features(${TARGET_NAME} PUBLIC cxx_std_20)
