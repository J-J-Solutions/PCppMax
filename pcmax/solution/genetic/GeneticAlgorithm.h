// Copyright (c) 2019                                          
//                                                                            
// Permission is hereby granted, free of charge, to any person obtaining a    
// copy of this software and associated documentation files (the "Software"), 
// to deal in the Software without restriction, including without limitation  
// the rights to use, copy, modify, merge, publish, distribute, sublicense,   
// and/or sell copies of the Software, and to permit persons to whom the      
// Software is furnished to do so, subject to the following conditions:       
//                                                                            
// The above copyright notice and this permission notice shall be included in 
// all copies or substantial portions of the Software.                        
//                                                                            
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING    
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER        
// DEALINGS IN THE SOFTWARE.                                                  
//                                                                            
//----------------------------------------------------------------------------

#ifndef PCMAX_GENETIC_ALGORITHM_H
#define PCMAX_GENETIC_ALGORITHM_H

#include <vector>
#include <random>
#include <algorithm>
#include "../Algorithm.h"

typedef std::random_device DEVICE;
typedef std::mt19937 MT;
typedef std::uniform_real_distribution<double> DISTRIBUTION;

template<typename T, typename U>
class GeneticAlgorithm : public Algorithm {
    DEVICE device;
    MT mt;
    DISTRIBUTION mutationDistribution;

    int maxPopulationSize;
    double mutationChance;
    int betterMax;
    int worseMax;
    std::vector<T> population;

    virtual T from(U u) = 0;

    virtual T breed(const T &t1, const T &t2) = 0;

    virtual void mutate(T &t) = 0;

    void breedNewPopulation();

    void breedNewMember(int t1, int t2);

public:
    GeneticAlgorithm(
            int initialPopulationSize,
            int maxPopulationSize,
            double mutationChance,
            double betterToAllRatio,
            U u);
};

template<typename T, typename U>
void GeneticAlgorithm<T, U>::breedNewPopulation() {
    auto populationSize = population.size();
    population.reserve(populationSize + populationSize * populationSize);

    for (int t1 = 0; t1 < populationSize; ++t1) {
        int t2 = 0;
        while (t2 < t1) breedNewMember(t1, t2++);
        while (++t2 < populationSize) breedNewMember(t1, t2);
    }

    if (population.size() > maxPopulationSize) {
        std::sort(population.begin(), population.end(), std::greater<>());
        population.erase(population.begin() + betterMax, population.end() - worseMax);
    }
}

template<typename T, typename U>
GeneticAlgorithm<T, U>::GeneticAlgorithm(
        int initialPopulationSize,
        int maxPopulationSize,
        double mutationChance,
        double betterToAllRatio,
        U u):
        maxPopulationSize(maxPopulationSize),
        mutationChance(mutationChance),
        mt(device()),
        mutationDistribution(DISTRIBUTION(0, 1)) {
    betterMax = std::floor(betterToAllRatio * maxPopulationSize);
    worseMax = maxPopulationSize - betterMax;
    for (int i = 0; i < initialPopulationSize; ++i) population.push_back(from(u));
}

template<typename T, typename U>
void GeneticAlgorithm<T, U>::breedNewMember(int t1, int t2) {
    T t = breed(population[t1], population[t2]);
    if (mutationChance > mutationDistribution(mt)) mutate(t);
    population.push_back(t);
}

#endif //PCMAX_GENETICALGORITHM_H
