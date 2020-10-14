cmake_minimum_required(VERSION 3.17)
project(spbu_2020_c_homeworks C)

set(CMAKE_C_STANDARD 11)

set(SOURCE_LIB
    library/commonUtils/numericOperations.c
)
add_library(library ${SOURCE_LIB})

add_executable(task1_1 homework1/task1.c)
add_executable(task1_2 homework1/task2.c)
target_link_libraries(task1_2 library)
add_executable(task1_3 homework1/task3.c)
add_executable(task1_4 homework1/task4.c)
add_executable(task1_5 homework1/task5.c)
target_link_libraries(task1_5 library)

add_executable(task2_1 homework2/task1.c)
add_executable(task2_2 homework2/task2.c)
add_executable(task2_4 homework2/task4.c)
target_link_libraries(task2_4 library)
add_executable(task2_5 homework2/task5.c)
