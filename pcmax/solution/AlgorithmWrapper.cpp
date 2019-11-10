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

#include <sstream>
#include <iostream>
#include <chrono>
#include "AlgorithmWrapper.h"

std::string AlgorithmWrapper::getTimeElapsed(
        long time1, const std::string &unit1,
        long time2, const std::string &unit2) {
    std::stringstream stream;
    stream << time1 << unit1;
    if (time2) stream << time2 << unit2;
    return stream.str();
}

void AlgorithmWrapper::solveWithFeedback(const Algorithm &algorithm, const Instance &instance) {
    auto begin = std::chrono::system_clock::now();
    auto solution = algorithm.solve(instance);
    auto end = std::chrono::system_clock::now();

    std::string timeElapsed;
    auto diff = end - begin;
    auto hours = std::chrono::duration_cast<std::chrono::hours>(diff).count();
    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(diff).count();
    if (hours) {
        minutes %= 60;
        timeElapsed = getTimeElapsed(hours, "h", minutes, "min");
    } else {
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(diff).count();
        if (minutes) {
            seconds %= 60;
            timeElapsed = getTimeElapsed(minutes, "min", seconds, "s");
        } else {
            auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
            if (seconds) {
                milliseconds %= 1000;
                timeElapsed = getTimeElapsed(seconds, "s", milliseconds, "ms");
            } else {
                auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(diff).count();
                if (milliseconds) {
                    microseconds %= 1000;
                    timeElapsed = getTimeElapsed(milliseconds, "ms", microseconds, "μs");
                } else {
                    auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count();
                    if (microseconds) {
                        nanoseconds %= 1000;
                        timeElapsed = timeElapsed = getTimeElapsed(microseconds, "μs", nanoseconds, "ns");
                    } else timeElapsed = getTimeElapsed(nanoseconds, "ns");
                }
            }
        }
    }

    std::cout << "Solution [" << solution << "] found in " << timeElapsed << std::endl;
}

void AlgorithmWrapper::solveWithFeedback(const Algorithm &algorithm) {
    Instance instance;
    std::cin >> instance;
    solveWithFeedback(algorithm, instance);
}
