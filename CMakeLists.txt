cmake_minimum_required(VERSION 3.15)
project(PCMax)

set(CMAKE_CXX_STANDARD 17)
add_executable(PCMaxGreedy
        pcmax/main.cpp
        pcmax/solution/base/Algorithm.h pcmax/solution/greedy/Algorithm.cpp
        pcmax/solution/Machine.h pcmax/solution/Machine.cpp
        pcmax/solution/TaskManager.h pcmax/solution/TaskManager.cpp)

add_executable(PCMaxHeuristic
        pcmax/main.cpp
        pcmax/solution/base/Algorithm.h pcmax/solution/heuristic/Algorithm.cpp
        pcmax/solution/Machine.h pcmax/solution/Machine.cpp
        pcmax/solution/TaskManager.h pcmax/solution/TaskManager.cpp)

add_executable(PCMaxBrutal
        pcmax/main.cpp
        pcmax/solution/base/Algorithm.h pcmax/solution/brutal/Algorithm.cpp
        pcmax/solution/Machine.h pcmax/solution/Machine.cpp
        pcmax/solution/TaskManager.h pcmax/solution/TaskManager.cpp)

add_executable(PCMaxGenetic
        pcmax/main.cpp
        pcmax/solution/base/Algorithm.h pcmax/solution/genetic/Algorithm.cpp
        pcmax/solution/Machine.h pcmax/solution/Machine.cpp
        pcmax/solution/TaskManager.h pcmax/solution/TaskManager.cpp)

add_executable(RandomGenerator
        pcmax/generator/random/main.cpp
        pcmax/generator/InstanceGenerator.h pcmax/generator/InstanceGenerator.cpp
        pcmax/generator/random/RandomInstanceGenerator.h pcmax/generator/random/RandomInstanceGenerator.cpp)

add_executable(OptimalGenerator
        pcmax/generator/optimal/main.cpp
        pcmax/generator/InstanceGenerator.h pcmax/generator/InstanceGenerator.cpp
        pcmax/generator/optimal/OptimalInstanceGenerator.h pcmax/generator/optimal/OptimalInstanceGenerator.cpp)
