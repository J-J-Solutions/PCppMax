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

#include <iostream>
#include <fstream>
#include "OptimalInstanceGenerator.h"

const std::string ABSOLUTE_PATH = "D:/CLionProjects/PCMax/pcmax/generator/optimal";

std::string instance(int n) {
    return ABSOLUTE_PATH + "/optimal_instance_" + std::to_string(n) + ".txt";
}

bool exists(const std::string &file) {
    std::ifstream stream(file);
    return stream.good();
}

int main() {
    int counter = 0;
    while (exists(instance(counter))) ++counter;

    std::cout << "How many instances would you like created?" << std::endl;
    int instances;
    std::cin >> instances;

    OptimalInstanceGenerator generator;
    while (instances--) {
        generator.generateNewInstance();
        generator.writeToFile(instance(counter++));
    }
}