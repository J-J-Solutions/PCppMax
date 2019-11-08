cmake_minimum_required(VERSION 3.15)
project(PCMax)

set(CMAKE_CXX_STANDARD 17)

add_executable(Greedy
        pcmax/solution/greedy/main.cpp
        pcmax/solution/base/Algorithm.h pcmax/solution/greedy/GreedyAlgorithm.h
        pcmax/solution/base/AlgorithmWrapper.h pcmax/solution/base/AlgorithmWrapper.cpp
        pcmax/solution/Machine.h pcmax/solution/Machine.cpp
        pcmax/solution/TaskManager.h pcmax/solution/TaskManager.cpp
        pcmax/instance/Instance.h pcmax/instance/Instance.cpp)

add_executable(Heuristic
        pcmax/solution/heuristic/main.cpp
        pcmax/solution/base/Algorithm.h pcmax/solution/heuristic/HeuristicAlgorithm.h
        pcmax/solution/base/AlgorithmWrapper.h pcmax/solution/base/AlgorithmWrapper.cpp
        pcmax/solution/Machine.h pcmax/solution/Machine.cpp
        pcmax/solution/TaskManager.h pcmax/solution/TaskManager.cpp
        pcmax/instance/Instance.h pcmax/instance/Instance.cpp)

add_executable(BruteForce
        pcmax/solution/brute-force/main.cpp
        pcmax/solution/base/Algorithm.h pcmax/solution/brute-force/BruteForceAlgorithm.h
        pcmax/solution/base/AlgorithmWrapper.h pcmax/solution/base/AlgorithmWrapper.cpp
        pcmax/solution/Machine.h pcmax/solution/Machine.cpp
        pcmax/solution/TaskManager.h pcmax/solution/TaskManager.cpp
        pcmax/instance/Instance.h pcmax/instance/Instance.cpp)

add_executable(Genetic
        pcmax/solution/genetic/main.cpp
        pcmax/solution/base/Algorithm.h pcmax/solution/genetic/GeneticAlgorithm.h
        pcmax/solution/base/AlgorithmWrapper.h pcmax/solution/base/AlgorithmWrapper.cpp
        pcmax/solution/Machine.h pcmax/solution/Machine.cpp
        pcmax/solution/TaskManager.h pcmax/solution/TaskManager.cpp
        pcmax/instance/Instance.h pcmax/instance/Instance.cpp)

add_executable(LTP
        pcmax/solution/ltp/main.cpp
        pcmax/solution/base/Algorithm.h pcmax/solution/ltp/LongestTimeProcessingAlgorithm.h
        pcmax/solution/base/AlgorithmWrapper.h pcmax/solution/base/AlgorithmWrapper.cpp
        pcmax/solution/Machine.h pcmax/solution/Machine.cpp
        pcmax/solution/TaskManager.h pcmax/solution/TaskManager.cpp
        pcmax/instance/Instance.h pcmax/instance/Instance.cpp)

add_executable(RandomGenerator
        pcmax/instance/generator/random/main.cpp
        pcmax/instance/generator/Generator.h pcmax/instance/generator/Generator.cpp
        pcmax/instance/generator/random/RandomGenerator.h pcmax/instance/generator/random/RandomGenerator.cpp
        pcmax/instance/Instance.h pcmax/instance/Instance.cpp)

add_executable(OptimalGenerator
        pcmax/instance/generator/optimal/main.cpp
        pcmax/instance/generator/Generator.h pcmax/instance/generator/Generator.cpp
        pcmax/instance/generator/optimal/OptimalGenerator.h pcmax/instance/generator/optimal/OptimalGenerator.cpp
        pcmax/instance/Instance.h pcmax/instance/Instance.cpp)
