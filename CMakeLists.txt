cmake_minimum_required(VERSION 3.20)
project(Homework_CS232 C)

set(CMAKE_C_STANDARD 99)

set(inClass OFF)

if (${inClass})
    add_executable(Homework_CS232 inClassWork/TestCode.c inClassWork/test_code.h project3/searchEngine.c project3/searchEngine.h)
else ()
    add_executable(Homework_CS232 project3/searchEngine.c project3/searchEngine.h)
endif ()

#add_executable(Homework_CS232 inClassWork/scratchFile.c)