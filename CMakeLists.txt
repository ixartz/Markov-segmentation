cmake_minimum_required(VERSION 2.8.11)

project(markov)

set(PROJECT_SRC_DIR ${PROJECT_SOURCE_DIR})

configure_file (
  "${PROJECT_SOURCE_DIR}/Settings.h.in"
  "${PROJECT_BINARY_DIR}/Settings.h")

include_directories("${PROJECT_BINARY_DIR}")

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
add_subdirectory(src)
