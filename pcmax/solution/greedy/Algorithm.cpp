#include "../base/Algorithm.h"
#include "../TaskManager.h"

using namespace std;

long long Algorithm::solve(int machines, int tasks, int *taskWorkTime) {
    TaskManager taskManager(machines);

    for (int t = 0; t < tasks; ++t) {
        auto machine = taskManager.pollShortestWorkingMachine();
        machine.addTask(taskWorkTime[t]);
        taskManager.addMachine(machine);
    }

    return taskManager.peekLongestWorkingMachine().getTotalWorkTime();
}
