cmake_minimum_required(VERSION 3.20) # Ensure C++23 support
project(adapter_factory)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(callable_traits INTERFACE)
target_include_directories(callable_traits INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Enable testing and add test directory
enable_testing()
add_subdirectory(test)
