cmake_minimum_required(VERSION 3.22)

# Set the project name
project(libltd VERSION 0.0.1)

# Set path variables
set(ROOT_DIR ${PROJECT_SOURCE_DIR})
set(INC_DIR ${ROOT_DIR}/inc)
set(SRC_DIR ${ROOT_DIR}/src)
set(TEST_DIR ${ROOT_DIR}/tests)

# Add source files
file(GLOB SOURCES ${SRC_DIR}/*.cpp)

# Create libltd.a static library
add_library(ltd STATIC ${SOURCES})
target_include_directories(ltd PUBLIC ${INC_DIR})

# Create test executable test_unit
add_executable(test_unit ${TEST_DIR}/test.cpp)
target_include_directories(test_unit PUBLIC ${INC_DIR})
target_link_libraries(test_unit ltd)

# Create test executable fmt_int
add_executable(fmt_int ${TEST_DIR}/fmt_int.cpp)
target_include_directories(fmt_int PUBLIC ${INC_DIR})
target_link_libraries(fmt_int ltd)

# Create test executable fmt_float
add_executable(fmt_float ${TEST_DIR}/fmt_float.cpp)
target_include_directories(fmt_float PUBLIC ${INC_DIR})
target_link_libraries(fmt_float ltd)

enable_testing()

# add_test(NAME Test COMMAND test_unit 0)
# set_tests_properties(Test
#  PROPERTIES PASS_REGULAR_EXPRESSION "-ok-"
# )

# define a function adding fmt_int
function(do_fmt_int_test target arg result)
  add_test(NAME Fmt-Int-${arg} COMMAND ${target} ${arg})
  set_tests_properties(Fmt-Int-${arg}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result}
    )
endfunction()

do_fmt_int_test(fmt_int 0 "-ok-")
do_fmt_int_test(fmt_int 1 "-ok-")
do_fmt_int_test(fmt_int 2 "-ok-")
do_fmt_int_test(fmt_int 3 "-ok-")
do_fmt_int_test(fmt_int 4 "-ok-")
do_fmt_int_test(fmt_int 5 "-ok-")
do_fmt_int_test(fmt_int 6 "-ok-")

function(do_fmt_float_test target arg result)
  add_test(NAME Fmt-Float-${arg} COMMAND ${target} ${arg})
  set_tests_properties(Fmt-Float-${arg}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result}
    )
endfunction()

do_fmt_float_test(fmt_float 0 "-ok-")
do_fmt_float_test(fmt_float 1 "-ok-")
do_fmt_float_test(fmt_float 2 "-ok-")
do_fmt_float_test(fmt_float 3 "-ok-")
do_fmt_float_test(fmt_float 4 "-ok-")
do_fmt_float_test(fmt_float 5 "-ok-")
do_fmt_float_test(fmt_float 6 "-ok-")

