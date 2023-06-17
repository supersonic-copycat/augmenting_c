cmake_minimum_required (VERSION 3.6.1)

project(AugmentingC)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_FLAGS "-Wall -std=gnu11 -ggdb -Wno-unused-variable ${CMAKE_C_FLAGS}")

include_directories( ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(AugmentingC main.c basics.c)
target_link_libraries(AugmentingC m)
