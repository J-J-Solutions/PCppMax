#include "../base/Algorithm.h"
#include "../TaskManager.h"
#include <algorithm>

using namespace std;

/*
 * Idea for heuristic algorithm:
 * Given a number of machines, number of tasks, and a duration of each task:
 * 1) Sort the task durations
 * 2) Calculate average time each machine will spend completing tasks.
 *    This average value is equal to the sum of task durations divided by the number of machines.
 * 3) For each machine:
 *    Assign longest available task and shortest available task alternately.
 *    Mark each assigned task as unavailable.
 *    When sum of durations of assigned tasks exceeds average, move on to the next machine.
 * 4) If there are any tasks left assign them according to the LPT algorithm (Longest Processing Time)
 * 5) Calculate how long it will take for all the tasks to complete (cmax)
 * 6) Assign the shortest task of the longest working machine to the shortest working machine.
 *    Calculate new cmax value.
 *    If it it better (smaller) than previous cmax value, repeat this step.
 *    Else cancel the assignment and end the algorithm
 */

long long Algorithm::solve(int machines, int tasks, int *taskWorkTime) {
    long long totalWorkTime = 0;

    for (int t = 0; t < tasks; ++t) totalWorkTime += taskWorkTime[t];

    long long averageWorkTime = totalWorkTime / machines;

    sort(taskWorkTime, taskWorkTime + tasks);

    TaskManager taskManager(machines);

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

    return pcMax;
}
