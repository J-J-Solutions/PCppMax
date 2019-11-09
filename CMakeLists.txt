cmake_minimum_required(VERSION 3.15)
project(PCMax)

set(CMAKE_CXX_STANDARD 17)

add_executable(Greedy
        pcmax/solution/greedy/main.cpp
        pcmax/solution/Algorithm.h pcmax/solution/greedy/GreedyAlgorithm.h
        pcmax/solution/AlgorithmWrapper.h pcmax/solution/AlgorithmWrapper.cpp
        pcmax/instance/Instance.h pcmax/instance/Instance.cpp
        pcmax/model/Task.cpp pcmax/model/Task.h
        pcmax/model/Worker.cpp pcmax/model/Worker.h
        pcmax/model/Scheduler.cpp pcmax/model/Scheduler.h)

add_executable(Heuristic
        pcmax/solution/heuristic/main.cpp
        pcmax/solution/Algorithm.h pcmax/solution/heuristic/HeuristicAlgorithm.h
        pcmax/solution/AlgorithmWrapper.h pcmax/solution/AlgorithmWrapper.cpp
        pcmax/instance/Instance.h pcmax/instance/Instance.cpp
        pcmax/model/Task.cpp pcmax/model/Task.h
        pcmax/model/Worker.cpp pcmax/model/Worker.h
        pcmax/model/Scheduler.cpp pcmax/model/Scheduler.h)

add_executable(BruteForce
        pcmax/solution/brute-force/main.cpp
        pcmax/solution/Algorithm.h pcmax/solution/brute-force/BruteForceAlgorithm.h
        pcmax/solution/AlgorithmWrapper.h pcmax/solution/AlgorithmWrapper.cpp
        pcmax/instance/Instance.h pcmax/instance/Instance.cpp
        pcmax/model/Task.cpp pcmax/model/Task.h
        pcmax/model/Worker.cpp pcmax/model/Worker.h
        pcmax/model/Scheduler.cpp pcmax/model/Scheduler.h)

add_executable(Genetic
        pcmax/solution/genetic/main.cpp
        pcmax/solution/Algorithm.h pcmax/solution/genetic/GeneticAlgorithm.h
        pcmax/solution/AlgorithmWrapper.h pcmax/solution/AlgorithmWrapper.cpp
        pcmax/instance/Instance.h pcmax/instance/Instance.cpp
        pcmax/model/Task.cpp pcmax/model/Task.h
        pcmax/model/Worker.cpp pcmax/model/Worker.h
        pcmax/model/Scheduler.cpp pcmax/model/Scheduler.h)

add_executable(LTP
        pcmax/solution/ltp/main.cpp
        pcmax/solution/Algorithm.h pcmax/solution/ltp/LongestTimeProcessingAlgorithm.h
        pcmax/solution/AlgorithmWrapper.h pcmax/solution/AlgorithmWrapper.cpp
        pcmax/instance/Instance.h pcmax/instance/Instance.cpp
        pcmax/model/Task.cpp pcmax/model/Task.h
        pcmax/model/Worker.cpp pcmax/model/Worker.h
        pcmax/model/Scheduler.cpp pcmax/model/Scheduler.h)

add_executable(RandomGenerator
        pcmax/instance/generator/random/main.cpp
        pcmax/instance/generator/Generator.h pcmax/instance/generator/Generator.cpp
        pcmax/instance/Instance.h pcmax/instance/Instance.cpp
        pcmax/instance/generator/GeneratorWrapper.h pcmax/instance/generator/GeneratorWrapper.cpp
        pcmax/instance/generator/random/RandomGenerator.h pcmax/instance/generator/random/RandomGenerator.cpp)

add_executable(OptimalGenerator
        pcmax/instance/generator/optimal/main.cpp
        pcmax/instance/generator/Generator.h pcmax/instance/generator/Generator.cpp
        pcmax/instance/Instance.h pcmax/instance/Instance.cpp
        pcmax/instance/generator/GeneratorWrapper.h pcmax/instance/generator/GeneratorWrapper.cpp
        pcmax/instance/generator/optimal/OptimalGenerator.h pcmax/instance/generator/optimal/OptimalGenerator.cpp)
