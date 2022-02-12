cmake_minimum_required(VERSION 3.12) 			

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -fsanitize=undefined -std=c++20")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic-errors -fsanitize=undefined -std=c++20")

project(Laba1)

add_executable(main0 main0.cpp DateAndTime.h DateAndTime.cpp)
add_executable(main1 main1.cpp BigNumber.h BigNumber.cpp)
add_executable(main2 main2.cpp YearFromAdam.h YearFromAdam.cpp)
add_executable(main3 main3.cpp Matrix.h Matrix.cpp)