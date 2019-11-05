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
OptimalInstanceGenerator::OptimalInstanceGenerator():
    InstanceGenerator(),
    solutionDistrubution(DISTRIBUTION(100, 1000)),
    optimalTaskDistrubtion(DISTRIBUTION(1, solution/2)){}
void OptimalInstanceGenerator::generateNewInstance() {
    delete[] taskWorkTime;
    machines = machineDistribution(mt);
    solution = solutionDistrubution(mt);
    solutionTimes = solution * machines;
    std::vector<int> taskWorkTime;
    int pom;
    for (int t = solutionTimes; t > 0; t-=pom) {
        pom = taskWorkTimeDistribution(mt);
        taskWorkTime.push_back(pom);
    }
    tasks = taskWorkTime.size();

    //TODO assign optimal solution value to 'solution' variable
    //TODO implement optimal instance generator based on 'solution' variable
}

void OptimalInstanceGenerator::writeToStream(std::ostream *output) {
    InstanceGenerator::writeToStream(output);
    *output << solution << std::endl;
}
