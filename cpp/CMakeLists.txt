cmake_minimum_required(VERSION 3.10)

project(lexer LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(tools)
add_subdirectory(src)
add_subdirectory(apps)
