cmake_minimum_required(VERSION 3.10)
project(c-containers)

set(CMAKE_C_STANDARD 99)

enable_testing()
find_package(GTest CONFIG REQUIRED)

macro(define_test arg)
    add_executable(${arg} "tests/${arg}.cc")
    target_link_libraries(${arg} PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
    add_test(${arg} ${arg})
endmacro()

define_test(test_stack)
define_test(test_queue)
define_test(test_vector)

add_executable(vector_example examples/vector_example.c)
add_executable(queue_example examples/queue_example.c)
add_executable(stack_example examples/stack_example.c)

