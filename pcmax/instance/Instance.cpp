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

Instance::Instance(int machines, int tasks, int *taskWorkTime) :
        machines(machines),
        tasks(tasks),
        taskWorkTime(taskWorkTime) {}

std::istream &operator>>(std::istream &input, Instance &instance) {
    delete[] instance.taskWorkTime;
    input >> instance.machines;
    input >> instance.tasks;
    instance.taskWorkTime = new int[instance.tasks];
    for (int t = 0; t < instance.tasks; ++t) {
        input >> instance.taskWorkTime[t];
    }
    return input;
}

std::ostream &operator<<(std::ostream &output, Instance &instance) {
    output << instance.machines << std::endl;
    output << instance.tasks << std::endl;
    for (int t = 0; t < instance.tasks; ++t) output << instance.taskWorkTime[t] << std::endl;
    return output;
}

Instance::~Instance() { delete[] taskWorkTime; }

int Instance::getMachines() const { return machines; }

void Instance::setMachines(int newMachines) { Instance::machines = newMachines; }

int Instance::getTasks() const { return tasks; }

void Instance::setTasks(int newTasks) { Instance::tasks = newTasks; }

int *Instance::getTaskWorkTime() const { return taskWorkTime; }

void Instance::setTaskWorkTime(int *newTaskWorkTime) { Instance::taskWorkTime = newTaskWorkTime; }
