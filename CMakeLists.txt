cmake_minimum_required(VERSION 3.17)
project(spbu_2020_c_homeworks C)

set(CMAKE_C_STANDARD 11)

set(SOURCE_LIB
    library/commonUtils/numericOperations.c
)
add_library(library ${SOURCE_LIB})

add_executable(task2_1 homework2/task1.c)