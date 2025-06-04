# Try to find a system-installed GTest first
find_package(GTest QUIET)

if (GTest_FOUND)
    message(STATUS "Using system-installed GoogleTest")
    # Try different module names that might be available
    if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/GoogleTest.cmake")
        include(GoogleTest)
    elseif(EXISTS "${CMAKE_CURRENT_LIST_DIR}/gtest.cmake")
        include(gtest)
    else()
        # If no module is found, we can still use the targets directly
        message(STATUS "No GoogleTest module found, using targets directly")
        # The GTest::gtest_main target should be available from find_package
        if(NOT TARGET GTest::gtest_main)
            # If the target isn't available, we need to fetch it
            message(STATUS "GTest targets not found, falling back to FetchContent")
            include(FetchContent)
            FetchContent_Declare(
              googletest
              URL https://github.com/google/googletest/archive/release-1.12.1.zip
            )
            # Avoid issues with MSVC runtime flags (safe to use on all platforms)
            set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
            FetchContent_MakeAvailable(googletest)
            include(GoogleTest)
        endif()
    endif()
    enable_testing()
else()
    message(STATUS "System GTest not found. Fetching GoogleTest...")
    include(FetchContent)
    FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/archive/release-1.12.1.zip
    )
    # Avoid issues with MSVC runtime flags (safe to use on all platforms)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    # When using FetchContent, we know the module will be available
    include(GoogleTest)
    enable_testing()
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

