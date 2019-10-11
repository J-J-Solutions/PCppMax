cmake_minimum_required(VERSION 3.15)
project(PCMax)

set(CMAKE_CXX_STANDARD 17)

add_executable(PCMaxGreedy pcmax.solution/greedy/main.cpp pcmax.solution/Machine.cpp pcmax.solution/Machine.h pcmax.solution/TaskManager.cpp pcmax.solution/TaskManager.h)
add_executable(PCMaxHeuristic pcmax.solution/heuristic/main.cpp pcmax.solution/Machine.cpp pcmax.solution/Machine.h pcmax.solution/TaskManager.cpp pcmax.solution/TaskManager.h)