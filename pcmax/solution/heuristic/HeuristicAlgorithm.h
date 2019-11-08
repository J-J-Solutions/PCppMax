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

#ifndef PCMAX_HEURISTIC_ALGORITHM_H
#define PCMAX_HEURISTIC_ALGORITHM_H

#include <algorithm>
#include "../base/Algorithm.h"
#include "../../model/Scheduler.h"

class HeuristicAlgorithm : public Algorithm {
protected:
    [[nodiscard]] static int balance(Scheduler scheduler) {
        auto possiblyLowerMax = scheduler.peekLastAvailableWorker().getTotalWorkTime();
        int pcMax;
        do {
            pcMax = possiblyLowerMax;
            auto longestWorkingMachine = scheduler.pollLastAvailableWorker();
            auto shortestWorkingMachine = scheduler.pollFirstAvailableWorker();
            shortestWorkingMachine.addTask(longestWorkingMachine.pollShortestTask());
            scheduler.addWorker(shortestWorkingMachine);
            scheduler.addWorker(longestWorkingMachine);
            possiblyLowerMax = scheduler.peekLastAvailableWorker().getTotalWorkTime();
        } while (possiblyLowerMax < pcMax);

        return pcMax;
    }

public:
    [[nodiscard]] int solve(const Instance &instance) const override {
        auto machines = instance.getMachines();
        auto tasks = instance.getTasks();
        auto taskDurations = instance.getTaskDurations();

        long long int totalWorkTime = 0;

        for (int t = 0; t < tasks; ++t) totalWorkTime += taskDurations[t];

        long long int averageWorkTime = totalWorkTime / machines;

        std::sort(taskDurations, taskDurations + tasks);

        Scheduler scheduler(machines);

        int lower = 0, upper = tasks - 1;
        for (int m = 0; m < machines && lower <= upper; ++m) {
            auto machine = scheduler.pollFirstAvailableWorker();
            while (machine.getTotalWorkTime() < averageWorkTime) {
                machine.addTask(Task(upper, taskDurations[upper]));
                --upper;
                if (machine.getTotalWorkTime() < averageWorkTime && lower <= upper) {
                    machine.addTask(Task(lower, taskDurations[lower]));
                    ++lower;
                } else break;
            }
            scheduler.addWorker(machine);
        }

        while (lower < upper) {
            auto machine = scheduler.pollFirstAvailableWorker();
            machine.addTask(Task(upper, taskDurations[upper]));
            --upper;
            scheduler.addWorker(machine);
        }

        return balance(scheduler);
    }
};

#endif //PCMAX_HEURISTICALGORITHM_H
