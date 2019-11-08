cmake_minimum_required(VERSION 3.15)
project(PCMax)

set(CMAKE_CXX_STANDARD 17)

add_executable(PCMaxGreedy
        pcmax/solution/greedy/main.cpp
        pcmax/solution/base/Algorithm.h pcmax/solution/greedy/GreedyAlgorithm.h
        pcmax/solution/Machine.h pcmax/solution/Machine.cpp
        pcmax/solution/TaskManager.h pcmax/solution/TaskManager.cpp pcmax/solution/base/AlgorithmWrapper.cpp pcmax/solution/base/AlgorithmWrapper.h pcmax/instance/Instance.cpp pcmax/instance/Instance.h)

add_executable(PCMaxHeuristic
        pcmax/solution/heuristic/main.cpp
        pcmax/solution/base/Algorithm.h pcmax/solution/heuristic/HeuristicAlgorithm.h
        pcmax/solution/Machine.h pcmax/solution/Machine.cpp
        pcmax/solution/TaskManager.h pcmax/solution/TaskManager.cpp pcmax/solution/base/AlgorithmWrapper.cpp pcmax/solution/base/AlgorithmWrapper.h pcmax/instance/Instance.cpp pcmax/instance/Instance.h)

add_executable(PCMaxBruteForce
        pcmax/solution/brute-force/main.cpp
        pcmax/solution/base/Algorithm.h pcmax/solution/brute-force/BruteForceAlgorithm.h
        pcmax/solution/Machine.h pcmax/solution/Machine.cpp
        pcmax/solution/TaskManager.h pcmax/solution/TaskManager.cpp pcmax/solution/base/AlgorithmWrapper.cpp pcmax/solution/base/AlgorithmWrapper.h pcmax/instance/Instance.cpp pcmax/instance/Instance.h)

add_executable(PCMaxGenetic
        pcmax/solution/genetic/main.cpp
        pcmax/solution/base/Algorithm.h pcmax/solution/genetic/GeneticAlgorithm.h
        pcmax/solution/Machine.h pcmax/solution/Machine.cpp
        pcmax/solution/TaskManager.h pcmax/solution/TaskManager.cpp pcmax/solution/base/AlgorithmWrapper.cpp pcmax/solution/base/AlgorithmWrapper.h pcmax/instance/Instance.cpp pcmax/instance/Instance.h)

add_executable(RandomGenerator
        pcmax/instance/generator/random/main.cpp
        pcmax/instance/generator/Generator.h pcmax/instance/generator/Generator.cpp
        pcmax/instance/generator/random/RandomGenerator.h pcmax/instance/generator/random/RandomGenerator.cpp
        pcmax/instance/Instance.cpp pcmax/instance/Instance.h)

add_executable(OptimalGenerator
        pcmax/instance/generator/optimal/main.cpp
        pcmax/instance/generator/Generator.h pcmax/instance/generator/Generator.cpp
        pcmax/instance/generator/optimal/OptimalGenerator.h pcmax/instance/generator/optimal/OptimalGenerator.cpp
        pcmax/instance/Instance.cpp pcmax/instance/Instance.h)
