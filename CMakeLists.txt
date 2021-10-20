cmake_minimum_required(VERSION 3.20)
project(Homework_CS232 C)

set(CMAKE_C_STANDARD 99)

set(inClass ON)

if (${inClass})
    add_executable(Homework_CS232 inClassWork/TestCode.c)
else ()
    add_executable(Homework_CS232 project1/crawler.c)
endif ()

#add_executable(Homework_CS232 inClassWork/scratchFile.c)