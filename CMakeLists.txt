cmake_minimum_required(VERSION 3.0)
project(Goosey C) 
set(CMAKE_C_STANDARD 99)   
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lncurses") 
include_directories(HEADER_FILE)
file(GLOB MAIN
    "main.c"
    "variables.h"
    )
add_executable(goosey ${MAIN})
add_custom_command(
    TARGET goosey POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $ENV{HOME}/.config/goosey
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:goosey> /usr/bin/
    COMMAND ${CMAKE_COMMAND} -E echo "alias goosey=/usr/bin/goosey" >> $ENV{HOME}/.bashrc
)
