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
#include <chrono>
#include <functional>
#include <iostream>
#include "../Algorithm.h"

typedef std::random_device DEVICE;
typedef std::mt19937 MT;
typedef std::uniform_real_distribution<double> DISTRIBUTION;

template<class T>
class GeneticAlgorithm : public Algorithm {
    DEVICE device;
    MT mt;
    DISTRIBUTION mutationDistribution;

    int initialPopulationSize, maxPopulationSize, betterMin, worseMax;
    double mutationChance, optimizationMinutes;

    void breedNewPopulation();

    void breedNewMember(int t1, int t2);

    std::vector<T *> population;

    void sortPopulationByScore();

    std::function<bool(T *, T *)> comparator;

protected:

    virtual T *initialMember(const Instance &instance) const = 0;

    virtual T *breed(T *t1, T *t2) const = 0;

    virtual T *mutate(T *t) const = 0;

//    std::function<int(T *)> score;

    virtual int score(T *t) const = 0;

public:
    enum OPTIMISATION { OPTIMISE_BY_MIN, OPTIMISE_BY_MAX };

    GeneticAlgorithm(
            int initialPopulationSize,
            int maxPopulationSize,
            double mutationChance,
            double betterToAllRatio,
            double optimisationDurationMinutes,
            OPTIMISATION optimisation
    );

    int solve(const Instance &instance) override;

    virtual ~GeneticAlgorithm();
};

template<class T>
void GeneticAlgorithm<T>::breedNewPopulation() {
    auto populationSize = population.size();
    population.reserve(populationSize + populationSize * populationSize);

    for (int t1 = 0; t1 < populationSize; ++t1) {
        int t2 = 0;
        while (t2 < t1) breedNewMember(t1, t2++);
        while (++t2 < populationSize) breedNewMember(t1, t2);
    }

    sortPopulationByScore();

    if (population.size() > maxPopulationSize)
        population.erase(population.begin() + betterMin, population.end() - worseMax);
}

template<class T>
GeneticAlgorithm<T>::GeneticAlgorithm(
        int initialPopulationSize,
        int maxPopulationSize,
        double mutationChance,
        double betterToAllRatio,
        double optimisationDurationMinutes,
        OPTIMISATION optimisation
) :
        initialPopulationSize(initialPopulationSize),
        maxPopulationSize(maxPopulationSize),
        mutationChance(mutationChance),
        optimizationMinutes(optimisationDurationMinutes),
        mt(device()),
        mutationDistribution(DISTRIBUTION(0, 1)) {
    betterMin = std::floor(betterToAllRatio * maxPopulationSize);
    worseMax = maxPopulationSize - betterMin;

    switch (optimisation) {
        case OPTIMISE_BY_MIN:
            comparator = [](T *t1, T *t2) { return (*t1) < (*t2); };
            break;
        case OPTIMISE_BY_MAX:
            comparator = [](T *t1, T *t2) { return (*t1) > (*t2); };
            break;
    }
}

template<class T>
void GeneticAlgorithm<T>::breedNewMember(int t1, int t2) {
    auto t = breed(population[t1], population[t2]);
    if (mutationChance > mutationDistribution(mt)) {
        population.push_back(mutate(t));
        delete t;
    } else population.push_back(t);
}

template<class T>
GeneticAlgorithm<T>::~GeneticAlgorithm() {
    for (T *t : population) delete t;
}

template<class T>
int GeneticAlgorithm<T>::solve(const Instance &instance) {
    population.reserve(initialPopulationSize);
    population.push_back(initialMember(instance));
    for (int i = 1; i < initialPopulationSize; ++i) population.push_back(mutate(population[i - 1]));

    sortPopulationByScore();
    int bestScore = score(population[0]);

    for (
            auto begin = std::chrono::system_clock::now(), end = begin;
            std::chrono::duration_cast<std::chrono::minutes>(end - begin).count() < optimizationMinutes;
            end = std::chrono::system_clock::now()) {
        std::cerr << "[" << score(population[0]) << ", " << score(*--population.end()) << "]" << std::endl;
        breedNewPopulation();
        bestScore = score(population[0]);
    }

    population.clear();
    return bestScore;
}

template<class T>
void GeneticAlgorithm<T>::sortPopulationByScore() {
    std::sort(population.begin(), population.end(), comparator);
}

#endif //PCMAX_GENETIC_ALGORITHM_H
