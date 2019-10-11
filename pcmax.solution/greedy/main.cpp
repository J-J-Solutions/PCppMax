#include "../TaskManager.h"
#include <iostream>

using namespace std;

/*template<typename T>
string contentToString(T *ts, int size, const string &prefix = "[", const string &separator = ", ",
                       const string &postfix = "]") {
    if (size <= 0) return "[]";
    stringstream str;
    str << prefix << ts[0];
    for (int i = 1; i < size; ++i) str << separator << ts[i];
    str << postfix;
    return str.str();
}*/

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