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

#ifndef PCMAX_BRUTEFORCEALGORITHM_H
#define PCMAX_BRUTEFORCEALGORITHM_H

#include <algorithm>
#include "../base/Algorithm.h"
#include "../TaskManager.h"

#define LONG_LONG_MAX 9223372036854775807

class BruteForceAlgorithm : public Algorithm {
public:
    long long int solve(int machines, int tasks, int *taskWorkTime) override {
        std::sort(taskWorkTime, taskWorkTime + tasks);

        long long pcMax = LONG_LONG_MAX;

        do {
            TaskManager taskManager(machines);

            for (int t = 0; t < tasks; ++t) {
                auto machine = taskManager.pollShortestWorkingMachine();
                machine.addTask(taskWorkTime[t]);
                taskManager.addMachine(machine);
            }

            pcMax = std::min(pcMax, taskManager.peekLongestWorkingMachine().getTotalWorkTime());
        } while (std::next_permutation(taskWorkTime, taskWorkTime + tasks));

        return pcMax;
    }
};

#endif //PCMAX_BRUTEFORCEALGORITHM_H
