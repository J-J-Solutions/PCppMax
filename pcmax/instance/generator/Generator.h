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

#ifndef PCMAX_INSTANCE_GENERATOR_H
#define PCMAX_INSTANCE_GENERATOR_H

#include <random>
#include "../Instance.h"

typedef std::random_device DEVICE;
typedef std::mt19937 MT;
typedef std::uniform_int_distribution<int> DISTRIBUTION;

class Generator {
protected:
    DEVICE device;
    MT mt;
    DISTRIBUTION machineDistribution;
    DISTRIBUTION taskDistribution;
    DISTRIBUTION taskWorkTimeDistribution;

    Instance *instance = nullptr;

    virtual std::string instanceName(int n) = 0;

    static bool exists(const std::string &instance);

    void writeInstanceToFile(const std::string &path);

    virtual void generateNewInstance();

public:
    Generator();

    void generateInstances(int n);

    [[nodiscard]] Instance *getInstance() const;

    virtual ~Generator();
};

#endif //PCMAX_INSTANCEGENERATOR_H