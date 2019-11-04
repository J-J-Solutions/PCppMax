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
