cmake_minimum_required(VERSION 3.18)

# Project configuration
project(hw02)
set(SUDOKU_SOURCES sudoku.c)
set(SOURCES main.c)
set(EXECUTABLE sudoku)
set(EXECUTABLE_TESTS sudoku-tests-cut)

# Executable
add_executable(${EXECUTABLE} ${SOURCES} ${SUDOKU_SOURCES})

# CUT Test files
file(GLOB TESTS_CUT "tests-cut/*.c")

# Test utility files
file(GLOB TESTS_LIBS_CUT "tests-cut/libs/*.c")

set(TEST_SOURCES
        ${TESTS_LIBS_CUT}
        ${TESTS_CUT}
        ${SUDOKU_SOURCES})

add_executable(${EXECUTABLE_TESTS} ${TEST_SOURCES})

# CLI Test Files
file(GLOB TESTS_CLI_SH "tests-cli/*.sh")
file(GLOB TESTS_CLI_DATA "tests-cli/data/*")

file(COPY ${TESTS_CLI_SH} "tests-cli/sudoku-tests-cli" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${TESTS_CLI_DATA} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data)

# Configure compiler warnings
if (CMAKE_C_COMPILER_ID MATCHES Clang OR ${CMAKE_C_COMPILER_ID} STREQUAL GNU)
  # using regular Clang, AppleClang or GCC
  # Strongly suggested: neable -Werror
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Wextra -pedantic")
elseif (${CMAKE_C_COMPILER_ID} STREQUAL MSVC)
  # using Visual Studio C++
  target_compile_definitions(${EXECUTABLE} PRIVATE _CRT_SECURE_NO_DEPRECATE)
  target_compile_definitions(${EXECUTABLE_TESTS} PRIVATE _CRT_SECURE_NO_DEPRECATE)
  set(CMAKE_CXX_FLAGS "/permissive- /W4 /EHsc")
endif()

if(MINGW)
    target_compile_definitions(${EXECUTABLE} PRIVATE __USE_MINGW_ANSI_STDIO=1)
    target_compile_definitions(${EXECUTABLE_TESTS} PRIVATE _CRT_SECURE_NO_DEPRECATE)
endif()
