cmake_minimum_required(VERSION 3.12) 			

SET(CMAKE_C_COMPILER clang)
SET(CMAKE_CXX_COMPILER clang++)

set(CMAKE_CXX_FLAGS
"${CMAKE_CXX_FLAGS} -Wall -pedantic-errors -fsanitize=undefined -std=c++20 -lgtest")

project(Laba2)

add_executable(main0 Test.cpp Vector.h Vector.cpp 
DateAndTime.h DateAndTime.cpp
BigNumber.h BigNumber.cpp 
YearFromAdam.cpp YearFromAdam.h 
Matrix.h Matrix.cpp)

add_executable(main1 Test1.cpp Stack.h Stack.cpp 
DateAndTime.h DateAndTime.cpp
BigNumber.h BigNumber.cpp 
YearFromAdam.cpp YearFromAdam.h 
Matrix.h Matrix.cpp)

add_executable(main2 Test2.cpp List.h List.cpp 
DateAndTime.h DateAndTime.cpp
BigNumber.h BigNumber.cpp
YearFromAdam.cpp YearFromAdam.h 
Matrix.h Matrix.cpp)

add_executable(main3 Test3.cpp Queue.h Queue.cpp 
DateAndTime.h DateAndTime.cpp
BigNumber.h BigNumber.cpp
YearFromAdam.cpp YearFromAdam.h 
Matrix.h Matrix.cpp)

add_executable(main4 Test4.cpp Tree.h Tree.cpp 
DateAndTime.h DateAndTime.cpp
BigNumber.h BigNumber.cpp
YearFromAdam.cpp YearFromAdam.h 
Matrix.h Matrix.cpp)