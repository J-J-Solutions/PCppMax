#include "../TaskManager.h"
#include <iostream>

using namespace std;

int main() {
    std::iostream::sync_with_stdio(false);

    int machines, tasks;
    cin >> machines >> tasks;

    TaskManager taskManager(machines);

    for (int i = 0, workTime; i < tasks; ++i) {
        cin >> workTime;
        auto machine = taskManager.pollShortestWorkingMachine();
        machine.addTask(workTime);
        taskManager.addMachine(machine);
    }

    cout << taskManager.peekLongestWorkingMachine().getTotalWorkTime() << endl;

    return 0;
}