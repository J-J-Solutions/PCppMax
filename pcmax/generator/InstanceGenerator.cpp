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
#include <fstream>
#include <iostream>
#include "InstanceGenerator.h"

InstanceGenerator::InstanceGenerator() :
        mt(device()),
        machineDistribution(DISTRIBUTION(1, 100)),
        taskDistribution(DISTRIBUTION(10, 100)),
        taskWorkTimeDistribution(DISTRIBUTION(20, 100)) {}

int InstanceGenerator::getMachines() const { return machines; }

int InstanceGenerator::getTasks() const { return tasks; }

int *InstanceGenerator::getTaskWorkTime() const { return taskWorkTime; }

void InstanceGenerator::writeToStream(std::ostream *output) {
    *output << machines << std::endl;
    *output << tasks << std::endl;
    for (int t = 0; t < tasks; ++t) *output << taskWorkTime[t] << std::endl;
}

void InstanceGenerator::writeToFile(const std::string &path) {
    std::cerr << path << std::endl;

    std::ofstream output(path);

    if (!output.is_open()) {
        std::cerr << "Cannot open file '" << path << "'" << std::endl;
        return;
    }

    writeToStream(&output);

    output.close();
}

