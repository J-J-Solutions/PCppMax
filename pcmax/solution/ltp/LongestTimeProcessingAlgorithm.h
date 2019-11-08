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

#ifndef PCMAX_LONGEST_TIME_PROCESSING_ALGORITHM_H
#define PCMAX_LONGEST_TIME_PROCESSING_ALGORITHM_H

#include <algorithm>
#include "../base/Algorithm.h"
#include "../greedy/GreedyAlgorithm.h"

class LongestTimeProcessingAlgorithm : public Algorithm {
public:
    [[nodiscard]] long long int solve(const Instance &instance) const override {
        int tasks = instance.getTasks();
        int *taskWorkTime = instance.getTaskWorkTime();
        std::sort(taskWorkTime, taskWorkTime + tasks, std::greater<>());
        return GreedyAlgorithm().solve(instance);
    }
};

typedef LongestTimeProcessingAlgorithm LTPAlgorithm;

#endif //PCMAX_LONGESTTIMEPROCESSINGALGORITHM_H
