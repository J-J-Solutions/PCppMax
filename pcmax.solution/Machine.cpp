#include "Machine.h"

using namespace std;

long long Machine::getTotalWorkTime() const { return totalWorkTime; }

void Machine::addTask(int workTime) {
    tasks[workTime]++;
    totalWorkTime += workTime;
}

int Machine::pollShortestTask() {
    auto it = tasks.begin();
    int duration = it->first;
    if (it->second-- == 1) tasks.erase(it);
    totalWorkTime -= duration;
    return duration;
}
