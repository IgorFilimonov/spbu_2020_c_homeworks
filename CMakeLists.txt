cmake_minimum_required(VERSION 3.17)
project(spbu_2020_c_homeworks C)

set(CMAKE_C_STANDARD 11)

set(SOURCE_LIB
        library/commonUtils/numericOperations.c
        library/commonUtils/arrayOperations.c
)

add_library(library ${SOURCE_LIB})
add_library(list library/list.c)
add_library(stack library/stack.c)
add_library(complexNumber library/complexNumber.c)
add_library(avl library/trees/bst_node.c library/trees/avl.c)
add_library(hashtable library/hashtable.c)
add_library(graph library/graph.c)
add_library(dfa library/dfa.c)
add_library(matrix library/matrix.c)
add_library(parser library/parser.c library/dfa.c)

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

add_executable(task1_t1 test1/task1.c)
target_link_libraries(task1_t1 list)
add_executable(task2_t1 test1/task2.c)
target_link_libraries(task2_t1 complexNumber)

add_executable(task5_2 homework5/task2.c)
target_link_libraries(task5_2 avl library)

add_executable(task1_t2 test2/task1.c)
add_executable(task2_t2 test2/task2.c)
add_executable(task3_t2 test2/task3.c)
target_link_libraries(task3_t2 graph)

add_executable(task6_1 homework6/task1.c)
target_link_libraries(task6_1 hashtable library)

add_executable(task7_1 homework7/task1.c)
target_link_libraries(task7_1 graph)
add_executable(task7_2 homework7/task2.c)
target_link_libraries(task7_2 graph list)

add_executable(task8_1 homework8/task1.c)
target_link_libraries(task8_1 library dfa)

add_executable(task2_t3 test3/task2.c)
target_link_libraries(task2_t3 matrix)

add_executable(task9_1 homework9/task1.c)
target_link_libraries(task9_1 parser library)
