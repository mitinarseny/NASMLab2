cmake_minimum_required(VERSION 3.15)
project(lab2 C)

set(CMAKE_C_STANDARD 11)
enable_language(ASM)
#set(CMAKE_C_FLAGS -masm=intel)
#set(CMAKE_C_FLAGS -m32)

add_executable(lab2 main.c)