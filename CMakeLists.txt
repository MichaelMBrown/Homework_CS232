cmake_minimum_required(VERSION 3.20)
project(Homework_CS232 C)

set(CMAKE_C_STANDARD 99)

set(inClass off)

if (${inClass})
    add_executable(Homework_CS232 inClassWork/odds.c inClassWork/odds.h inClassWork/matcher.c)
else ()
    add_executable(Homework_CS232 project3/searchEngine.c project3/searchEngine.h inClassWork/odds.c inClassWork/odds.h inClassWork/matcher.c)
endif ()