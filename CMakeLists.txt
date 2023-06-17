cmake_minimum_required (VERSION 3.6.1)

project(AugmentingC)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_FLAGS "-Wall -std=gnu11 -ggdb -Wno-unused-variable ${CMAKE_C_FLAGS}")

find_package(Guile)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} ${Guile_INCLUDE_DIR})

add_executable(AugmentingC main.c)
target_link_libraries(AugmentingC ${Guile_LIBRARIES} m)
