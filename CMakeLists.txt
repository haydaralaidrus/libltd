cmake_minimum_required(VERSION 3.22)

# Set the project name
project(ltd VERSION 0.0.1)

# Set path variables
set(ROOT_DIR ${PROJECT_SOURCE_DIR})
set(INC_DIR ${ROOT_DIR}/include)
set(SRC_DIR ${ROOT_DIR}/source)
set(TEST_DIR ${ROOT_DIR}/tests) 

# Add source files
file(GLOB SOURCES ${SRC_DIR}/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES ${INC_DIR}/*.hpp)

# Create libltd.a static library
add_library(ltd STATIC ${SOURCES})
target_include_directories(ltd PUBLIC ${INC_DIR})

# Create test executable test_unit
add_executable(cli_test ${TEST_DIR}/cli_test.cpp)
target_include_directories(cli_test PUBLIC ${INC_DIR})
target_link_libraries(cli_test ltd)

# Create test executable fmt_int
add_executable(fmt_int ${TEST_DIR}/fmt_int.cpp)
target_include_directories(fmt_int PUBLIC ${INC_DIR})
target_link_libraries(fmt_int ltd)

# Create test executable fmt_float
add_executable(fmt_float ${TEST_DIR}/fmt_float.cpp)
target_include_directories(fmt_float PUBLIC ${INC_DIR})
target_link_libraries(fmt_float ltd)

# Create test executable fmt_string
add_executable(fmt_string ${TEST_DIR}/fmt_string.cpp)
target_include_directories(fmt_string PUBLIC ${INC_DIR})
target_link_libraries(fmt_string ltd)

# Create test executable fmt_string
add_executable(raii_ptr ${TEST_DIR}/raii_ptr.cpp)
target_include_directories(raii_ptr PUBLIC ${INC_DIR})
target_link_libraries(raii_ptr ltd)

enable_testing()

add_test(NAME Cli-Flags COMMAND cli_test -a)
set_tests_properties(Cli-Flags
PROPERTIES PASS_REGULAR_EXPRESSION "-ok-"
)

add_test(NAME Fmt-Int COMMAND fmt_int -a)
set_tests_properties(Fmt-Int
PROPERTIES PASS_REGULAR_EXPRESSION "-ok-"
)

add_test(NAME Fmt-Float COMMAND fmt_float -a)
set_tests_properties(Fmt-Float
PROPERTIES PASS_REGULAR_EXPRESSION "-ok-"
)

add_test(NAME Fmt-Str COMMAND fmt_string -a)
set_tests_properties(Fmt-Str
PROPERTIES PASS_REGULAR_EXPRESSION "-ok-"
)

# Installation and Deployment
set_target_properties(ltd
    PROPERTIES
    PUBLIC_HEADER "${INCLUDE_FILES}"
)

install (TARGETS ltd
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include/ltd
)