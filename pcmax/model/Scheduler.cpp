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
    while (workers--) addWorker(new Worker);
}

void Scheduler::addWorker(Worker *worker) {
    workers[worker->getTotalWorkTime()].push_back(worker);
}

Worker *Scheduler::pollWorker(ITERATOR iterator) {
    auto worker = iterator->second.front();
    iterator->second.pop_front();
    if (iterator->second.empty()) workers.erase(iterator);
    return worker;
}

Worker *Scheduler::peekLastAvailableWorker() const {
    return workers.rbegin()->second.front();
}

Worker *Scheduler::pollFirstAvailableWorker() {
    return pollWorker(workers.begin());
}

Worker *Scheduler::pollLastAvailableWorker() {
    return pollWorker(--workers.end());
}

WORKERS Scheduler::asWorkers() const {
    WORKERS list;
    for (const auto &pair : workers)
        for (const auto &worker: pair.second)
            list.push_back(worker);
    return list;
}

Scheduler *Scheduler::fromWorkers(const WORKERS &workers) {
    auto scheduler = new Scheduler;
    for (const auto &worker: workers) scheduler->addWorker(worker);
    return scheduler;
}

Scheduler::~Scheduler() {
    for (const auto &pair: workers)
        for (const auto &worker: pair.second)
            delete worker;
}

bool Scheduler::operator<(const Scheduler &rhs) const {
    return peekLastAvailableWorker()->getTotalWorkTime() < rhs.peekLastAvailableWorker()->getTotalWorkTime();
}

bool Scheduler::operator>(const Scheduler &rhs) const {
    return rhs < *this;
}
