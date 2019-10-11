#include "Algorithm.h"
#include <iostream>
#include <chrono>

using namespace std;

int main() {
    iostream::sync_with_stdio(false);
    int machines, tasks;
    std::cin >> machines >> tasks;

    int *taskWorkTime = new int[tasks];
    for (int t = 0; t < tasks; ++t) std::cin >> taskWorkTime[t];

    auto begin = std::chrono::system_clock::now();
    long long solution = Algorithm::solve(machines, tasks, taskWorkTime);
    auto end = std::chrono::system_clock::now();
    std::cout << "Solution found in "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()
              << " [ns]" << std::endl;

    delete[] taskWorkTime;

    cout << solution << endl;

    return 0;
}