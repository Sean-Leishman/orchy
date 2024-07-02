set(LIBRARY_NAME lexer_lib)

add_library(${LIBRARY_NAME} lexer.cpp scanner.cpp token.cpp)

target_include_directories(${LIBRARY_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/include")

target_compile_features(lexer_lib PUBLIC cxx_std_17)

source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
