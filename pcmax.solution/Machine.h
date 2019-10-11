#ifndef PCMAX_MACHINE_H
#define PCMAX_MACHINE_H

#include <map>

class Machine {
    long long totalWorkTime = 0L;

    std::map<int, int> tasks;
public:
    void addTask(int workTime);

    int pollShortestTask();

    [[nodiscard]] long long getTotalWorkTime() const;
};

#endif //PCMAX_MACHINE_H
