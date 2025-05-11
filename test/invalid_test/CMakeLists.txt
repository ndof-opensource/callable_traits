cmake_minimum_required(VERSION 3.20)
project(invalid_concepts_compile_check LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(callable_traits REQUIRED)

add_executable(invalid_concepts_test invalid_concepts_test.cpp)
target_link_libraries(invalid_concepts_test PRIVATE callable_traits::callable_traits)

