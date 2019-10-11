#include "Algorithm.h"
#include <iostream>
#include <chrono>

using namespace std;

int main() {
    iostream::sync_with_stdio(false);

    int machines, tasks;
    cin >> machines >> tasks;

    int *taskWorkTime = new int[tasks];
    for (int t = 0; t < tasks; ++t) cin >> taskWorkTime[t];

    auto begin = chrono::system_clock::now();
    long long solution = Algorithm::solve(machines, tasks, taskWorkTime);
    auto end = chrono::system_clock::now();
    cout << "Solution found in "
         << chrono::duration_cast<chrono::nanoseconds>(end - begin).count()
         << " [ns]" << endl;

    delete[] taskWorkTime;

    cout << solution << endl;

    return 0;
}