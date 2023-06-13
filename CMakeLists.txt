cmake_minimum_required (VERSION 3.6.1)

project(AugmentingC)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_FLAGS "-Wall -std=gnu11 -ggdb -Wno-unused-variable ${CMAKE_C_FLAGS}")

add_executable(AugmentingC main.c)
