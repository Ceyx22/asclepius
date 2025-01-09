#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <functional>
#include <queue>
#include <vector>
#include <chrono>
#include <thread>
#include <iostream>

namespace util {
    struct Task {
        int priority;
        std::string name;
        std::function<void()> callback;
        std::chrono::steady_clock::time_point nextRunTime;
        std::chrono::milliseconds interval;

        bool operator<(const Task &other) const {
            return priority < other.priority;
        }
    };

    class Scheduler {
    private:
        std::priority_queue<Task> taskQueue;

    public:
        void addTask(const std::string &name, int priority, const std::function<void()> &callback,
                     std::chrono::milliseconds interval = std::chrono::milliseconds(0));


        void run();
    };
}


#endif // SCHEDULER_H
