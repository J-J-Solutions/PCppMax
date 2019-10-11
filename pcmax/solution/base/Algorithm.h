#ifndef PCMAX_ALGORITHM_H
#define PCMAX_ALGORITHM_H

#include <chrono>
#include <iostream>

class Algorithm {
public:
    static long long solve() {
        int machines, tasks;
        std::cin >> machines >> tasks;

        int *taskWorkTime = new int[tasks];
        for (int t = 0, workTime; t < tasks; ++t) std::cin >> taskWorkTime[t];

        auto begin = std::chrono::system_clock::now();
        long long solution = solve(machines, tasks, taskWorkTime);
        auto end = std::chrono::system_clock::now();
        std::cout << "Solution found in "
                  << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()
                  << " [ns]" << std::endl;

        delete[] taskWorkTime;

        return solution;
    }

    static long long solve(int machines, int tasks, int *taskWorkTime);
};

#endif //PCMAX_ALGORITHM_H
