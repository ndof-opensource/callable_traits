# Try to find a system-installed GTest first
find_package(GTest QUIET)

if(NOT GTest_FOUND)
  message(STATUS "System GTest not found — using FetchContent to download GoogleTest.")
  
  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
  )

  # Avoid issues with MSVC runtime flags (safe to use on all platforms)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

  FetchContent_MakeAvailable(googletest)
endif()

# Find our package
find_package(callable_traits REQUIRED)

# Valid concept tests
add_executable(test_callable_concepts test_callable_concepts.cpp)
target_link_libraries(test_callable_concepts PRIVATE GTest::gtest_main callable_traits::callable_traits)

add_test(NAME CallableConceptsTest COMMAND test_callable_concepts)

# Optional: compile-fail test (not built unless you uncomment below)
# add_executable(invalid_concepts_test invalid_concepts_test.cpp)
# target_link_libraries(invalid_concepts_test PRIVATE callable_traits::callable_traits)

