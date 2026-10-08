cmake_minimum_required(VERSION 3.19)
project(huffman-archiver VERSION 1.2.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

option(ENABLE_SANITIZERS "Build with AddressSanitizer and UndefinedBehaviorSanitizer" OFF)
option(BUILD_TESTS       "Build unit and integration tests"                           OFF)
option(BUILD_BENCHMARKS  "Build the benchmarking tool"                                OFF)

if(ENABLE_SANITIZERS)
    if(NOT CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        message(WARNING "ENABLE_SANITIZERS is only supported with GCC or Clang")
    else()
        message(STATUS "Sanitizers: ON")
        add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer -g -O0)
        add_link_options   (-fsanitize=address,undefined)
    endif()
endif()

add_subdirectory(app/core)
add_subdirectory(app/cli)

# if(BUILD_TESTS)
#     enable_testing()
#     add_subdirectory(tests)
# endif()

# if(BUILD_BENCHMARKS)
#     add_subdirectory(benchmarks)
# endif()
