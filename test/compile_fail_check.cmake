# test/compile_fail_check.cmake

cmake_minimum_required(VERSION 3.20)
message(STATUS "Checking that invalid concept usage fails to compile...")

# Configure try_compile
try_compile(COMPILE_SUCCEEDED
  "${CMAKE_BINARY_DIR}/compile_fail"
  "${CMAKE_SOURCE_DIR}/test"
  invalid_concepts_test.cpp
  CMAKE_FLAGS
    "-DINCLUDE_DIRECTORIES=${CMAKE_SOURCE_DIR}/include"
    "-DCMAKE_CXX_STANDARD=23"
    "-DCMAKE_CXX_STANDARD_REQUIRED=ON"
    "-DCMAKE_CXX_EXTENSIONS=OFF"
  OUTPUT_VARIABLE OUTPUT
)

if(COMPILE_SUCCEEDED)
  message(FATAL_ERROR
    "Expected invalid_concepts_test.cpp to fail compilation, but it succeeded.\nOutput:\n${OUTPUT}")
else()
  message(STATUS "✅ invalid_concepts_test.cpp correctly failed to compile.")
endif()

