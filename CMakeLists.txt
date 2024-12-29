cmake_minimum_required(VERSION 3.00)
project(Goosey C) # Put C,C++ or anything in place of XX 
set(CMAKE_C_CSTANDART 99)    # Specify standard of language in place of STANDARD  
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lncurses") # Specify flags and libraries of corresponding language in place of FLAGSANDLIBRARIES
include_directories(HEADER_FILE)
file(GLOB MAIN
    "main.c"
    "variables.c"
    )
    add_executable(goosey ${MAIN})