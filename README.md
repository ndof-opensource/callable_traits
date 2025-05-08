# Callable Traits

![CI](https://github.com/ndof-opensource/callable_traits/actions/workflows/ci.yml/badge.svg)

A C++23+ header-only library for tools for callable objects.

## Installation

### Using FetchContent (Recommended)

The easiest way to use this library is through CMake's FetchContent. Add the following to your CMakeLists.txt:

```cmake
include(FetchContent)

# Fetch the library
FetchContent_Declare(
    callable_traits
    GIT_REPOSITORY https://github.com/ndof-opensource/callable_traits.git
    GIT_TAG main  # or any specific tag/commit
)

# Make it available
FetchContent_MakeAvailable(callable_traits)

# Create your executable
add_executable(my_program main.cpp)
```

That's it! Since this is a header-only library, FetchContent will automatically set up the include directories for you. No additional linking is required.

You can also specify a specific version or commit:

```cmake
# Using a specific version
FetchContent_Declare(
    callable_traits
    GIT_REPOSITORY https://github.com/ndof-opensource/callable_traits.git
    GIT_TAG v1.0.0  # specific version
)

# Or using a specific commit
FetchContent_Declare(
    callable_traits
    GIT_REPOSITORY https://github.com/ndof-opensource/callable_traits.git
    GIT_TAG abc123...  # specific commit hash
)
```

### Build Options

You can control various build options when using FetchContent:

```cmake
# Set options before making the content available
set(CALLABLE_TRAITS_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(CALLABLE_TRAITS_INSTALL_ALL ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(callable_traits)
```

Available options:
- `CALLABLE_TRAITS_BUILD_TESTS`: Build the test suite (default: OFF)
- `CALLABLE_TRAITS_INSTALL_ALL`: Install all headers (default: ON)
- `CALLABLE_TRAITS_INSTALL_CONCEPTS`: Install callable_concepts.hpp (default: ON)
- `CALLABLE_TRAITS_INSTALL_ARGUMENT_HELPER`: Install callable_argument_helper.hpp (default: ON)
- `CALLABLE_TRAITS_INSTALL_TYPE_GENERATOR`: Install callable_type_generator.hpp (default: ON)
- `CALLABLE_TRAITS_INSTALL_UTILS`: Install callable_utils.hpp (default: ON)
- `CALLABLE_TRAITS_INSTALL_QUALIFIED_BY`: Install qualified_by.hpp (default: ON)
- `CALLABLE_TRAITS_INSTALL_QUALIFIERS`: Install callable_qualifiers.hpp (default: ON)
- `CALLABLE_TRAITS_INSTALL_TRAITS`: Install callable_traits.hpp (default: ON)

### Manual Installation

If you prefer to install the library manually:

```bash
git clone https://github.com/ndof-opensource/callable_traits.git
cd callable_traits
mkdir build && cd build
cmake ..
cmake --build .
cmake --install .
```

Then in your CMakeLists.txt:

```cmake
find_package(callable_traits REQUIRED)
```

## Usage

After installation, you can include the headers in your code:

```cpp
#include <callable_traits/callable_traits.hpp>
// ... other headers as needed
```

## Requirements

- C++23 or later
- CMake 3.20 or later
