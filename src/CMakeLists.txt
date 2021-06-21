
set( LIB_INCLUDE_DIR ../include)
set( CMAKE_CXX_STANDARD 11)
include_directories(${LIB_INCLUDE_DIR})
#add_library(asm-parser-lib STATIC *.cpp ${LIB_INCLUDE_DIR})
add_library(asm-parser-lib STATIC 
    assembler.cpp
    instr.cpp
    label.cpp
    parameter.cpp
)
