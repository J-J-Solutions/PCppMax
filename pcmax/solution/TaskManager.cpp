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

#include "TaskManager.h"

using namespace std;

TaskManager::TaskManager(int machines) {
    MACHINES init;
    while (machines--) { init.emplace_back(); }
    this->machines[0] = init;
}

void TaskManager::addMachine(const Machine &machine) {
    machines[machine.getTotalWorkTime()].push_back(machine);
}

Machine TaskManager::pollShortestWorkingMachine() { return pollMachine(machines.begin()); }

Machine TaskManager::pollLongestWorkingMachine() { return pollMachine(--machines.end()); }

Machine TaskManager::pollMachine(ITERATOR iterator) {
    auto machine = iterator->second.front();
    iterator->second.pop_front();
    if (iterator->second.empty()) machines.erase(iterator);
    return machine;
}

Machine TaskManager::peekLongestWorkingMachine() const { return peekMachine(--machines.end()); }

Machine TaskManager::peekMachine(CONST_ITERATOR iterator) const { return iterator->second.front(); }
