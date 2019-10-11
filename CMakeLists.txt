cmake_minimum_required(VERSION 3.15)
project(PCMax)

set(CMAKE_CXX_STANDARD 17)
add_executable(PCMaxGreedy pcmax/solution/greedy/Algorithm.cpp pcmax/solution/base/Algorithm.h pcmax/solution/Machine.cpp pcmax/solution/Machine.h pcmax/solution/TaskManager.cpp pcmax/solution/TaskManager.h pcmax/solution/base/main.cpp)
add_executable(PCMaxHeuristic pcmax/solution/heuristic/Algorithm.cpp pcmax/solution/base/Algorithm.h pcmax/solution/Machine.cpp pcmax/solution/Machine.h pcmax/solution/TaskManager.cpp pcmax/solution/TaskManager.h pcmax/solution/base/main.cpp)
add_executable(PCMaxBrutal pcmax/solution/brutal/Algorithm.cpp pcmax/solution/base/Algorithm.h pcmax/solution/Machine.cpp pcmax/solution/Machine.h pcmax/solution/TaskManager.cpp pcmax/solution/TaskManager.h pcmax/solution/base/main.cpp)