cmake_minimum_required(VERSION 3.12)

project(pingudb VERSION 1.0
                DESCRIPTION "A database that just works"
                LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14 CACHE STRING "C++ standard to conform to")
set(CMAKE_CXX_STANDARD_REQUIRED)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "Create indexing for clangd") # works

add_subdirectory(lib)

add_subdirectory(tools)
