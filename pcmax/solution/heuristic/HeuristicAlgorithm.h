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
#include "../TaskManager.h"

class HeuristicAlgorithm : public Algorithm {
public:
    [[nodiscard]] long long int solve(const Instance &instance) const override {
        int machines = instance.getMachines();
        int tasks = instance.getTasks();
        int *taskWorkTime = instance.getTaskWorkTime();

        long long totalWorkTime = 0;

        for (int t = 0; t < tasks; ++t) totalWorkTime += taskWorkTime[t];

        long long averageWorkTime = totalWorkTime / machines;

        std::sort(taskWorkTime, taskWorkTime + tasks);

        TaskManager taskManager(machines);

        int lower = 0, upper = tasks - 1;
        for (int m = 0; m < machines && lower <= upper; ++m) {
            auto machine = taskManager.pollShortestWorkingMachine();
            while (machine.getTotalWorkTime() < averageWorkTime) {
                machine.addTask(taskWorkTime[upper--]);
                if (machine.getTotalWorkTime() < averageWorkTime && lower <= upper)
                    machine.addTask(taskWorkTime[lower++]);
                else break;
            }
            taskManager.addMachine(machine);
        }

        while (lower < upper) {
            auto machine = taskManager.pollShortestWorkingMachine();
            machine.addTask(taskWorkTime[upper--]);
            taskManager.addMachine(machine);
        }

        long long possiblyLowerMax = taskManager.peekLongestWorkingMachine().getTotalWorkTime(), pcMax;
        do {
            pcMax = possiblyLowerMax;
            auto shortestWorkingMachine = taskManager.pollShortestWorkingMachine();
            auto longestWorkingMachine = taskManager.pollLongestWorkingMachine();
            shortestWorkingMachine.addTask(longestWorkingMachine.pollShortestTask());
            taskManager.addMachine(shortestWorkingMachine);
            taskManager.addMachine(longestWorkingMachine);
            possiblyLowerMax = taskManager.peekLongestWorkingMachine().getTotalWorkTime();
        } while (possiblyLowerMax < pcMax);

        return pcMax;
    }
};

#endif //PCMAX_HEURISTICALGORITHM_H
