set(LIBRARY_NAME lexer_lib)
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

add_library(${LIBRARY_NAME} "")
target_include_directories(${LIBRARY_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_sources(${LIBRARY_NAME} PUBLIC ${SOURCE_DIR}/lexer.cpp ${SOURCE_DIR}/scanner.cpp ${SOURCE_DIR}/token.cpp ${SOURCE_DIR}/printer.cpp ${SOURCE_DIR}/expression.cpp) 


target_compile_features(lexer_lib PUBLIC cxx_std_17)

source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
