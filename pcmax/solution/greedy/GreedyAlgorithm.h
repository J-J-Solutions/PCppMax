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

#ifndef PCMAX_GREEDY_ALGORITHM_H
#define PCMAX_GREEDY_ALGORITHM_H

#include "../Algorithm.h"
#include "../../model/Scheduler.h"

class GreedyAlgorithm : public Algorithm {
public:
    [[nodiscard]] int solve(const Instance &instance) override {
        int machines = instance.getWorkers();
        int tasks = instance.getTasks();
        int *taskDurations = instance.getTaskDurations();

        Scheduler scheduler(machines);

        for (int t = 0; t < tasks; ++t) {
            auto worker = scheduler.pollFirstAvailableWorker();
            worker->addTask(new Task(t, taskDurations[t]));
            scheduler.addWorker(worker);
        }

        return scheduler.peekLastAvailableWorker()->getTotalWorkTime();
    }
};

#endif //PCMAX_GREEDYALGORITHM_H
