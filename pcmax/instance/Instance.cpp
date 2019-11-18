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

#include "Instance.h"

Instance::Instance(int workers, int tasks, int *taskDurations, int solution) :
        workers(workers),
        tasks(tasks),
        taskDurations(taskDurations),
        solution(solution) {}

std::istream &operator>>(std::istream &input, Instance &instance) {
    delete[] instance.taskDurations;
    input >> instance.workers;
    input >> instance.tasks;
    instance.taskDurations = new int[instance.tasks];
    for (int t = 0; t < instance.tasks; ++t) input >> instance.taskDurations[t];
    input >> instance.solution;

    return input;
}

std::ostream &operator<<(std::ostream &output, Instance &instance) {
    output << instance.workers << std::endl;
    output << instance.tasks << std::endl;
    for (int t = 0; t < instance.tasks; ++t) output << instance.taskDurations[t] << std::endl;
    output << instance.solution << std::endl;

    return output;
}

int Instance::getWorkers() const { return workers; }

int Instance::getTasks() const { return tasks; }

int *Instance::getTaskDurations() const { return taskDurations; }

int Instance::getSolution() const { return solution; }

Instance::~Instance() { delete[] taskDurations; }
