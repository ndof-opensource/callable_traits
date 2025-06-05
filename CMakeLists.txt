cmake_minimum_required(VERSION 3.20) # Ensure C++23 support
project("callable_traits" VERSION 1.0.0
                            DESCRIPTION "A header-only C++ library that provides tools for callable objects."
                            HOMEPAGE_URL "https://github.com/ndof-opensource/callable_traits.git")

# Check if compiler supports C++23
include(CheckCXXSourceCompiles)
message(STATUS "Checking C++23 support...")
message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "CMAKE_CXX_COMPILER_VERSION: ${CMAKE_CXX_COMPILER_VERSION}")

# Try to compile a small C++23 program
set(CMAKE_REQUIRED_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")
check_cxx_source_compiles("
    #include <version>
    #include <iostream>
    
    // Test some basic C++23 features
    #if __cplusplus >= 202302L
        void test() {
            // Test if constexpr if is supported
            if constexpr (true) {
                std::cout << \"C++23 supported\\n\";
            }
        }
        int main() { return 0; }
    #else
        #error C++23 not supported
    #endif
" CXX23_SUPPORTED)
message(STATUS "C++23 support check result: ${CXX23_SUPPORTED}")

if(NOT CXX23_SUPPORTED)
    message(FATAL_ERROR "Your compiler does not support C++23. Please use a more recent compiler version.")
endif()

# For Clang, check if libc++ is available
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_REQUIRED_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    check_cxx_source_compiles("
        #include <iostream>
        int main() { return 0; }
    " LIBCXX_AVAILABLE)
    
    if(LIBCXX_AVAILABLE)
        add_compile_options(-stdlib=libc++)
        add_link_options(-stdlib=libc++)
        message(STATUS "Using libc++ standard library")
    else()
        message(WARNING "libc++ not found, falling back to libstdc++. This might cause issues with C++23 features.")
    endif()
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Option to enable/disable tests
option(CALLABLE_TRAITS_BUILD_TESTS "Build the test suite" OFF)

# Options for individual header installation
option(CALLABLE_TRAITS_INSTALL_ALL "Install all headers" ON)
option(CALLABLE_TRAITS_INSTALL_CONCEPTS "Install callable_concepts.hpp" OFF)
option(CALLABLE_TRAITS_INSTALL_ARGUMENT_HELPER "Install callable_argument_helper.hpp" OFF)
option(CALLABLE_TRAITS_INSTALL_TYPE_GENERATOR "Install callable_type_generator.hpp" OFF)
option(CALLABLE_TRAITS_INSTALL_UTILS "Install callable_utils.hpp" OFF)
option(CALLABLE_TRAITS_INSTALL_QUALIFIED_BY "Install qualified_by.hpp" OFF)
option(CALLABLE_TRAITS_INSTALL_QUALIFIERS "Install callable_qualifiers.hpp" OFF)
option(CALLABLE_TRAITS_INSTALL_TRAITS "Install callable_traits.hpp" OFF)

include(GNUInstallDirs)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(
    callable_traits
    INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
              $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_23)

# Only enable testing and add test directory if tests are enabled
if(CALLABLE_TRAITS_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}_Targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}_config.cmake.in"
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION
    ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)

install(
    EXPORT ${PROJECT_NAME}_Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)

install(
    FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
          "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)

# Install headers based on options
if(CALLABLE_TRAITS_INSTALL_ALL)
    install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ndof-os/callable_traits DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ndof-os)
else()
    # Create a list of files to install based on options
    set(HEADERS_TO_INSTALL)
    if(CALLABLE_TRAITS_INSTALL_CONCEPTS)
        list(APPEND HEADERS_TO_INSTALL "callable_concepts.hpp")
    endif()
    if(CALLABLE_TRAITS_INSTALL_ARGUMENT_HELPER)
        list(APPEND HEADERS_TO_INSTALL "callable_argument_helper.hpp")
    endif()
    if(CALLABLE_TRAITS_INSTALL_TYPE_GENERATOR)
        list(APPEND HEADERS_TO_INSTALL "callable_type_generator.hpp")
    endif()
    if(CALLABLE_TRAITS_INSTALL_UTILS)
        list(APPEND HEADERS_TO_INSTALL "callable_utils.hpp")
    endif()
    if(CALLABLE_TRAITS_INSTALL_QUALIFIED_BY)
        list(APPEND HEADERS_TO_INSTALL "qualified_by.hpp")
    endif()
    if(CALLABLE_TRAITS_INSTALL_QUALIFIERS)
        list(APPEND HEADERS_TO_INSTALL "callable_qualifiers.hpp")
    endif()
    if(CALLABLE_TRAITS_INSTALL_TRAITS)
        list(APPEND HEADERS_TO_INSTALL "callable_traits.hpp")
    endif()

    # Install selected headers
    foreach(header ${HEADERS_TO_INSTALL})
        install(FILES ${PROJECT_SOURCE_DIR}/include/ndof-os/callable_traits/${header}
                DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ndof-os)
    endforeach()
endif()
