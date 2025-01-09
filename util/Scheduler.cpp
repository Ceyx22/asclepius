#include "Scheduler.h"

namespace util {
    void Scheduler::addTask(const std::string &name, int priority, const std::function<void()> &callback,
                            std::chrono::milliseconds interval) {
        Task newTask;
        newTask.name = name;
        newTask.priority = priority;
        newTask.callback = callback;
        newTask.nextRunTime = std::chrono::steady_clock::now() + interval;
        newTask.interval = interval;
        taskQueue.push(newTask);
    }

    void Scheduler::run() {
        while (!taskQueue.empty()) {
            Task currentTask = taskQueue.top();
            taskQueue.pop();

            auto now = std::chrono::steady_clock::now();
            if (now >= currentTask.nextRunTime) {
                std::cout << "Executing task: " << currentTask.name << "\n";
                currentTask.callback();

                if (currentTask.interval.count() > 0) {
                    currentTask.nextRunTime = now + currentTask.interval;
                    taskQueue.push(currentTask);
                }
            } else {
                // If the task's time hasn't come, push it back and sleep for a while
                taskQueue.push(currentTask);
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        }
    }
}

