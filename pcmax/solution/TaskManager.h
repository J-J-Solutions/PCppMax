// Copyright (c) 2019 J&J Solutions
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

#ifndef PCMAX_TASK_MANAGER_H
#define PCMAX_TASK_MANAGER_H

#include "Machine.h"
#include <list>

typedef std::list<Machine, std::allocator<Machine>> MACHINES;
typedef std::pair<const long long, MACHINES> ENTRY;
typedef std::_Rb_tree_iterator<ENTRY> ITERATOR;
typedef std::_Rb_tree_const_iterator<ENTRY> CONST_ITERATOR;

class TaskManager {
    std::map<long long, MACHINES> machines;

    [[nodiscard]] Machine peekMachine(CONST_ITERATOR iterator) const;

    Machine pollMachine(ITERATOR iterator);

public:
    explicit TaskManager(int machines);

    void addMachine(const Machine &machine);

    Machine pollShortestWorkingMachine();

    [[nodiscard]] Machine peekLongestWorkingMachine() const;

    Machine pollLongestWorkingMachine();
};

#endif //PCMAX_TASK_MANAGER_H
