cmake_minimum_required(VERSION 3.17)
project(spbu_2020_c_homeworks C)

set(CMAKE_C_STANDARD 11)

set(SOURCE_LIB
        library/commonUtils/numericOperations.c
        library/commonUtils/arrayOperations.c
)

add_library(complexNumber library/complexNumber.c)
add_library(library ${SOURCE_LIB})
add_library(list library/list.c)
add_library(stack library/stack.c)


add_executable(task1_1 homework1/task1.c)
add_executable(task1_2 homework1/task2.c)
target_link_libraries(task1_2 library)
add_executable(task1_3 homework1/task3.c)
add_executable(task1_4 homework1/task4.c)
add_executable(task1_5 homework1/task5.c)
target_link_libraries(task1_5 library)

add_executable(task2_1 homework2/task1.c)
add_executable(task2_2 homework2/task2.c)
add_executable(task2_3 homework2/task3.c)
target_link_libraries(task2_3 library)
add_executable(task2_4 homework2/task4.c)
target_link_libraries(task2_4 library)
add_executable(task2_5 homework2/task5.c)

add_executable(task3_2 homework3/task2.c)
target_link_libraries(task3_2 list)

add_executable(task4_1 homework4/task1.c)
target_link_libraries(task4_1 library)
target_link_libraries(task4_1 stack)
add_executable(task4_3 homework4/task3.c)

add_executable(task2_t1 test1/task2.c)
target_link_libraries(task2_t1 complexNumber)
