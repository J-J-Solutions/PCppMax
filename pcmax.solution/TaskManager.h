#ifndef PCMAX_TASKMANAGER_H
#define PCMAX_TASKMANAGER_H

#include "Machine.h"
#include <list>

typedef std::list<Machine, std::allocator<Machine>> MACHINES;
typedef std::_Rb_tree_iterator<std::pair<const long long, MACHINES>> ITERATOR;
typedef std::_Rb_tree_const_iterator<std::pair<const long long, MACHINES>> CONST_ITERATOR;

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

#endif //PCMAX_TASKMANAGER_H
