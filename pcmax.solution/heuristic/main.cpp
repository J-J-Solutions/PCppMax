#include "../TaskManager.h"
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    std::iostream::sync_with_stdio(false);

    int machines, tasks;
    cin >> machines >> tasks;
    long long totalWorkTime = 0;

    TaskManager taskManager(machines);

    int *taskWorkTime = new int[tasks];
    for (int t = 0, workTime; t < tasks; ++t) {
        cin >> workTime;
        totalWorkTime += workTime;
        taskWorkTime[t] = workTime;
    }

    long long averageWorkTime = totalWorkTime / machines;

    sort(taskWorkTime, taskWorkTime + tasks);

    int lower = 0, upper = tasks - 1;
    for (int m = 0; m < machines && lower <= upper; ++m) {
        auto machine = taskManager.pollShortestWorkingMachine();
        while (machine.getTotalWorkTime() < averageWorkTime) {
            machine.addTask(taskWorkTime[upper--]);
            if (machine.getTotalWorkTime() < averageWorkTime && lower <= upper)
                machine.addTask(taskWorkTime[lower++]);
            else break;
        }
        taskManager.addMachine(machine);
    }

    while (lower < upper) {
        auto machine = taskManager.pollShortestWorkingMachine();
        machine.addTask(taskWorkTime[upper--]);
        taskManager.addMachine(machine);
    }

    delete[] taskWorkTime;

    long long possiblyLowerMax = taskManager.peekLongestWorkingMachine().getTotalWorkTime(), pcMax;
    do {
        pcMax = possiblyLowerMax;
        auto shortestWorkingMachine = taskManager.pollShortestWorkingMachine();
        auto longestWorkingMachine = taskManager.pollLongestWorkingMachine();
        shortestWorkingMachine.addTask(longestWorkingMachine.pollShortestTask());
        taskManager.addMachine(shortestWorkingMachine);
        taskManager.addMachine(longestWorkingMachine);
        possiblyLowerMax = taskManager.peekLongestWorkingMachine().getTotalWorkTime();
    } while (possiblyLowerMax < pcMax);

    cout << pcMax << endl;

    return 0;
}