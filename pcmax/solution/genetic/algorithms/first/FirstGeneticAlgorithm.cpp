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

#include "FirstGeneticAlgorithm.h"

Scheduler *FirstGeneticAlgorithm::breed(Scheduler *scheduler1, Scheduler *scheduler2) const {
    auto workers1 = scheduler1->asWorkers();
    auto workers2 = scheduler2->asWorkers();

    auto scheduler = new Scheduler;

    auto w1 = workers1.begin(), w2 = workers2.begin();
    while (w1 != workers1.end() && w2 != workers2.end()) {
        auto worker = new Worker;

        copyTasks((*w1++)->asTasks(), even, worker);
        copyTasks((*w2++)->asTasks(), odd, worker);

        scheduler->addWorker(worker);
    }

    while (w1 != workers1.end())
        scheduler->addWorker(copyTasks((*w1++)->asTasks(), even));

    while (w2 != workers2.end())
        scheduler->addWorker(copyTasks((*w2++)->asTasks(), odd));

    return scheduler;
}

Scheduler *FirstGeneticAlgorithm::mutate(Scheduler *scheduler) const {
    auto mutated = new Scheduler;
    for (const auto &worker : scheduler->asWorkers())
        mutated->addWorker(copyTasks(worker->asTasks()));

    auto firstAvailableWorker = mutated->pollFirstAvailableWorker();
    auto lastAvailableWorker = mutated->pollLastAvailableWorker();

    firstAvailableWorker->addTask(lastAvailableWorker->pollShortestTask());

    mutated->addWorker(firstAvailableWorker);
    mutated->addWorker(lastAvailableWorker);

    return mutated;
}

FirstGeneticAlgorithm::FirstGeneticAlgorithm() :
        GeneticAlgorithm(
                10,
                100,
                0.1,
                0.5,
                5,
                GeneticAlgorithm::OPTIMISE_BY_MIN
        ) {}

int FirstGeneticAlgorithm::score(Scheduler *scheduler) const {
    return scheduler->peekLastAvailableWorker()->getTotalWorkTime();
}

Scheduler *FirstGeneticAlgorithm::initialMember(const Instance &instance) const {
    int workers = instance.getWorkers();
    int tasks = instance.getTasks();
    int *taskDurations = instance.getTaskDurations();

    auto scheduler = new Scheduler(workers);
    for (int t = 0; t < tasks; ++t) {
        auto worker = scheduler->pollFirstAvailableWorker();
        worker->addTask(new Task(t, taskDurations[t]));
        scheduler->addWorker(worker);
    }

    return scheduler;
}

Worker *FirstGeneticAlgorithm::copyTasks(const TASKS &tasks, const TASK_PREDICATE &predicate, Worker *worker) {
    for (const auto &task: tasks)
        if (predicate(task))
            worker->addTask(task);
        else delete task;
    return worker;
}
