cmake_minimum_required( VERSION 3.2 )
project(AssemblerParser)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(src)
add_executable( parser main.cpp)

target_include_directories(parser PRIVATE include)
target_link_libraries( parser asm-parser-lib)
