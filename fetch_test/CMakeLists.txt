cmake_minimum_required(VERSION 3.20)
project(fetch_test)

# Set C++23 flags
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Use FetchContent to get GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/release-1.12.1.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Use FetchContent to get callable_traits
FetchContent_Declare(
    callable_traits
    GIT_REPOSITORY https://github.com/ndof-opensource/callable_traits.git
    GIT_TAG main
)

# Configure options for callable_traits
set(CALLABLE_TRAITS_BUILD_TESTS OFF CACHE BOOL "" FORCE)

# Make the library available
FetchContent_MakeAvailable(callable_traits)

# Copy the test file from the main test directory
configure_file(
    ${CMAKE_SOURCE_DIR}/../test/test_callable_concepts.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/test_callable_concepts.cpp
    COPYONLY
)

# Add our test executable
add_executable(test_callable_concepts test_callable_concepts.cpp)
target_link_libraries(test_callable_concepts PRIVATE GTest::gtest_main callable_traits)

# Enable testing
enable_testing()
add_test(NAME CallableConceptsTest COMMAND test_callable_concepts) 