cmake_minimum_required(VERSION 3.12) 			

SET(CMAKE_C_COMPILER clang)
SET(CMAKE_CXX_COMPILER clang++)

set(CMAKE_CXX_FLAGS
"${CMAKE_CXX_FLAGS} -Wall -pedantic-errors -fsanitize=undefined -std=c++20 -lgtest")

#target_link_libraries(${CMAKE_PROJECT_NAME} "-lgtest")

#set(CMAKE_LD_FLAGS
#"${CMAKE_LD_FLAGS} -lgtest")

project(Laba3)

add_executable(main0 Test.cpp Vector.h)

add_executable(main1 Test1.cpp Stack.h)

add_executable(main2 Test2.cpp List.hpp)

add_executable(main3 Test3.cpp Queue.hpp)

add_executable(main4 Test4.cpp Tree.hpp)