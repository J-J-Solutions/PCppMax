#include "../base/Algorithm.h"
#include "../TaskManager.h"
#include <algorithm>

#define LLONG_LONG_MAX 9223372036854775807

using namespace std;

long long Algorithm::solve(int machines, int tasks, int *taskWorkTime) {
    sort(taskWorkTime, taskWorkTime + tasks);

    long long pcMax = LLONG_LONG_MAX;

    do {
        TaskManager taskManager(machines);

        for (int t = 0; t < tasks; ++t) {
            auto machine = taskManager.pollShortestWorkingMachine();
            machine.addTask(taskWorkTime[t]);
            taskManager.addMachine(machine);
        }

        pcMax = min(pcMax, taskManager.peekLongestWorkingMachine().getTotalWorkTime());
        cout << "Current PCMax: " << pcMax << endl;
    } while (next_permutation(taskWorkTime, taskWorkTime + tasks));

    return pcMax;
}
