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

#ifndef PCMAX_FIRST_GENETIC_ALGORITHM_H
#define PCMAX_FIRST_GENETIC_ALGORITHM_H

#include "../../GeneticAlgorithm.h"
#include "../../../../model/Scheduler.h"

typedef std::function<bool(Task *)> TASK_PREDICATE;

class FirstGeneticAlgorithm : public GeneticAlgorithm<Scheduler> {
    TASK_PREDICATE even = [](Task *task) { return task->getID() % 2 == 0; };
    TASK_PREDICATE odd = [](Task *task) { return task->getID() % 2 == 1; };

    static Worker *copyTasks(
            const TASKS &tasks,
            const TASK_PREDICATE &predicate = [](Task *task) { return true; },
            Worker *worker = new Worker);

protected:
    Scheduler *breed(Scheduler *scheduler1, Scheduler *scheduler2) const override;

    Scheduler *mutate(Scheduler *scheduler) const override;

    [[nodiscard]] Scheduler *initialMember(const Instance &instance) const override;

    int score(Scheduler *scheduler) const override;

public:
    FirstGeneticAlgorithm();
};

#endif //PCMAX_FIRST_GENETIC_ALGORITHM_H
