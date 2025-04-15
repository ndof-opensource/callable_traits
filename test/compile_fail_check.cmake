cmake_minimum_required(VERSION 3.20)
project(invalid_concepts_compile_check)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

try_compile(SHOULD_FAIL
    "${CMAKE_BINARY_DIR}/compile_fail"
    "${CMAKE_SOURCE_DIR}/test"
    invalid_concepts_test.cpp
    CMAKE_FLAGS "-DINCLUDE_DIRECTORIES=${CMAKE_SOURCE_DIR}/include"
    OUTPUT_VARIABLE COMPILE_OUTPUT
)

if(SHOULD_FAIL)
    message(FATAL_ERROR "Expected compilation to fail, but it succeeded:\n${COMPILE_OUTPUT}")
else()
    message(STATUS "Invalid concept test correctly failed to compile.")
endif()

