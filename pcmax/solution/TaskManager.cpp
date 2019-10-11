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
