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

#include <ostream>
#include "OptimalInstanceGenerator.h"

OptimalInstanceGenerator::OptimalInstanceGenerator() :
        InstanceGenerator(),
        solutionDistribution(DISTRIBUTION(100, 1000)) {}

void OptimalInstanceGenerator::generateNewInstance() {
    delete[] taskWorkTime;
    machines = machineDistribution(mt);
    solution = solutionDistribution(mt);
    int solutionTimes = solution * machines;
    std::vector<int> tasksVector;
    int task;
    for (int t = solutionTimes; t > 0; t -= task) {
        task = taskWorkTimeDistribution(mt);
        tasksVector.push_back(task);
    }
    tasks = tasksVector.size();
    taskWorkTime = new int[tasks];
    std::copy(tasksVector.begin(), tasksVector.end(), taskWorkTime);
}

std::ostream &operator<<(std::ostream &os, const OptimalInstanceGenerator &generator) {
    os << static_cast<const InstanceGenerator &>(generator);
    os << generator.solution << std::endl;
    return os;
}

std::string OptimalInstanceGenerator::instanceName(int n) {
    return "optimal_instance_" + std::to_string(n) + ".txt";
}
