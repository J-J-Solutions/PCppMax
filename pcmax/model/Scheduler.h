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

#ifndef PCMAX_SCHEDULER_H
#define PCMAX_SCHEDULER_H

#include <list>
#include <map>
#include <vector>
#include "Worker.h"

typedef std::list<Worker *> WORKERS;
typedef std::pair<const int, WORKERS> ENTRY;
typedef std::_Rb_tree_iterator<ENTRY> ITERATOR;

class Scheduler {

    std::map<int, WORKERS> workers;

    Worker *pollWorker(ITERATOR iterator);

public:
    explicit Scheduler(int workers = 0);

    static Scheduler *fromWorkers(const WORKERS &workers);

    void addWorker(Worker *worker);

    Worker *pollFirstAvailableWorker();

    [[nodiscard]] Worker *peekLastAvailableWorker() const;

    Worker *pollLastAvailableWorker();

    [[nodiscard]] WORKERS asWorkers() const;

    bool operator<(const Scheduler &rhs) const;

    bool operator>(const Scheduler &rhs) const;

    virtual ~Scheduler();
};

#endif //PCMAX_SCHEDULER_H
