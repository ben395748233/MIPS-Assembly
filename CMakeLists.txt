
cmake_minimum_required(VERSION 3.20)

project(
    MipsArchitectureLab
    VERSION 0.1.0
    LANGUAGES CXX
)

# C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---------------------------------
# Compiler warnings
# ---------------------------------

function(mipslab_set_warnings target)
    if(MSVC)
        target_compile_options(${target} PRIVATE
            /W4
            /permissive-
            /EHsc
        )
    else()
        target_compile_options(${target} PRIVATE
            -Wall
            -Wextra
            -Wpedantic
        )
    endif()
endfunction()

# ---------------------------------
# Core Library
# ---------------------------------

add_library(mipslab_core STATIC
    "MipsLab.Core/CPUState.cpp"
    "MipsLab.Core/Logger.cpp"
)

target_include_directories(mipslab_core PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/MipsLab.Core"
)

mipslab_set_warnings(mipslab_core)

# The existing MSBuild project uses pch.h.
# CMake initially compiles CPUState.cpp without PCH.
# Remove its first #include "pch.h" or enable PCH in CMake.

target_precompile_headers(mipslab_core PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/MipsLab.Core/pch.h"
)

# ---------------------------------
# CLI
# ---------------------------------

add_executable(mipslab
    "MIPS Assembly/MIPS Assembly.cpp"
)

target_link_libraries(mipslab PRIVATE
    mipslab_core
)

mipslab_set_warnings(mipslab)

# ---------------------------------
# Tests
# ---------------------------------

include(CTest)

if(BUILD_TESTING)
    add_executable(mipslab_tests
        "MipsLab.Tests/CPUStateTests.cpp"
    )

    target_link_libraries(mipslab_tests PRIVATE
        mipslab_core
    )

    mipslab_set_warnings(mipslab_tests)

    add_test(
        NAME CPUStateTests
        COMMAND mipslab_tests
    )
    add_test(
    NAME CLI_Help
    COMMAND mipslab --help
)

add_test(
    NAME CLI_Version
    COMMAND mipslab --version
)

add_test(
    NAME CLI_InvalidArgument
    COMMAND mipslab --invalid
)

set_tests_properties(
    CLI_InvalidArgument
    PROPERTIES
        WILL_FAIL TRUE
)
# Logger / Configuration Tests
add_executable(mipslab_logger_tests
    "MipsLab.Tests/LoggerConfigTests.cpp"
)

target_link_libraries(mipslab_logger_tests PRIVATE
    mipslab_core
)

if(MSVC)
    target_compile_options(mipslab_logger_tests PRIVATE
        /W4
        /permissive-
        /EHsc
    )
endif()

add_test(
    NAME LoggerConfigTests
    COMMAND mipslab_logger_tests
)
endif()
