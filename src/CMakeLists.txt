cmake_minimum_required(VERSION 3.12)

project(pingudb VERSION 1.0
                DESCRIPTION "A database that just works"
                LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14 CACHE STRING "C++ standard to conform to")
set(CMAKE_CXX_STANDARD_REQUIRED)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "Create indexing for clangd")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(lib)

add_subdirectory(tools)
