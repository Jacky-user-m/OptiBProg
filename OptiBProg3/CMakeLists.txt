cmake_minimum_required(VERSION 3.10)

project(OptiBProg3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmax-errors=2")

add_library(readLgf readLgf.cpp)
add_library(randomVertex randomVertex.cpp)
add_library(bipartition MyBipartition.cpp)
add_library(mwmatching MyMaxWeightedMatching.cpp)
add_library(readFootball FootballBettingGameParser.cpp)
add_library(betting MyFootballBettingGame.cpp)
add_library(maxflow MyMaxFlow.cpp)
add_library(check check.cpp)

add_executable(Main main.cpp)
target_link_libraries(Main readLgf randomVertex bipartition mwmatching readFootball betting maxflow check)
