#include "Algorithm.h"
#include <iostream>
#include <chrono>
#include <sstream>

using namespace std;

string getTimeElapsed(long time1, const string &unit1, long time2 = 0, const string &unit2 = "") {
    stringstream s;
    s << time1 << unit1;
    if (time2) s << time2 << unit2;
    return s.str();
}

int main() {
    iostream::sync_with_stdio(false);

    int machines, tasks;
    cin >> machines >> tasks;

    int *taskWorkTime = new int[tasks];
    for (int t = 0; t < tasks; ++t) cin >> taskWorkTime[t];

    auto begin = chrono::system_clock::now();
    long long solution = Algorithm::solve(machines, tasks, taskWorkTime);
    auto end = chrono::system_clock::now();

    delete[] taskWorkTime;

    string timeElapsed;
    auto diff = end - begin;
    auto hours = chrono::duration_cast<chrono::hours>(diff).count();
    auto minutes = chrono::duration_cast<chrono::minutes>(diff).count();
    if (hours == 0) {
        auto seconds = chrono::duration_cast<chrono::seconds>(diff).count();
        if (minutes == 0) {
            auto milliseconds = chrono::duration_cast<chrono::milliseconds>(diff).count();
            if (seconds == 0) {
                auto microseconds = chrono::duration_cast<chrono::microseconds>(diff).count();
                if (milliseconds == 0) {
                    auto nanoseconds = chrono::duration_cast<chrono::nanoseconds>(diff).count();
                    if (microseconds == 0) timeElapsed = getTimeElapsed(nanoseconds, "ns");
                    else {
                        nanoseconds %= 1000;
                        timeElapsed = timeElapsed = getTimeElapsed(microseconds, "μs", nanoseconds, "ns");
                    }
                } else {
                    microseconds %= 1000;
                    timeElapsed = getTimeElapsed(milliseconds, "ms", microseconds, "μs");
                }
            } else {
                milliseconds %= 1000;
                timeElapsed = getTimeElapsed(seconds, "s", milliseconds, "ms");
            }
        } else {
            seconds %= 60;
            timeElapsed = getTimeElapsed(minutes, "min", seconds, "s");
        }
    } else {
        minutes %= 60;
        timeElapsed = getTimeElapsed(hours, "h", minutes, "min");
    }

    cout << "Solution [" << solution << "] found in " << timeElapsed << endl;

    return 0;
}