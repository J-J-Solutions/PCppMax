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

#ifndef PCMAX_BRUTE_FORCE_ALGORITHM_H
#define PCMAX_BRUTE_FORCE_ALGORITHM_H

#include <algorithm>
#include "../Algorithm.h"
#include "../greedy/GreedyAlgorithm.h"

#define LONG_LONG_MAX 2147483647

class BruteForceAlgorithm : public Algorithm {
    GreedyAlgorithm greedyAlgorithm;

public:
    [[nodiscard]] int solve(const Instance &instance) override {
        int tasks = instance.getTasks();
        int *taskDurations = instance.getTaskDurations();

        std::sort(taskDurations, taskDurations + tasks);

        int pcMax = LONG_LONG_MAX;

        do {
            pcMax = std::min(pcMax, greedyAlgorithm.solve(instance));
        } while (std::next_permutation(taskDurations, taskDurations + tasks));

        return pcMax;
    }
};

#endif //PCMAX_BRUTEFORCEALGORITHM_H
