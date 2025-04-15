cmake_minimum_required(VERSION 3.20)
project(invalid_concepts_compile_check LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${CMAKE_CURRENT_LIST_DIR}/../../include)

add_executable(invalid_concepts_test ../invalid_concepts_test.cpp)

