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

#include "Scheduler.h"

Scheduler::Scheduler(int workers) {
    WORKERS init;
    while (workers--) init.push_back(Worker());
    this->workers[0] = init;
}

void Scheduler::addWorker(const Worker &worker) {
    workers[worker.getTotalWorkTime()].push_back(worker);
}

Worker Scheduler::pollWorker(ITERATOR iterator) {
    auto machine = iterator->second.front();
    iterator->second.pop_front();
    if (iterator->second.empty()) workers.erase(iterator);
    return machine;
}

Worker Scheduler::peekLastAvailableWorker() const {
    return workers.rbegin()->second.front();
}

Worker Scheduler::pollFirstAvailableWorker() {
    return pollWorker(workers.begin());
}

Worker Scheduler::pollLastAvailableWorker() {
    return pollWorker(--workers.end());
}

Worker *Scheduler::toWorkersArray(int size) const {
    auto machineArray = new Worker[size];
    int m = 0;
    for (const auto &pair : this->workers)
        for (const auto &machine : pair.second)
            machineArray[m++] = machine;
    return machineArray;
}

Scheduler Scheduler::fromWorkersArray(Worker *workers, int size) {
    Scheduler scheduler(0);
    for (int m = 0; m < size; ++m) scheduler.addWorker(workers[m]);
    return scheduler;
}
