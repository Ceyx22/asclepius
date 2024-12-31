//
// Created by ceyx on 12/30/24.
//

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <functional>
#include <queue>
#include <thread>
#include <condition_variable>

namespace util {
    class Scheduler {
    public:
        explicit Scheduler(size_t threadCount);

        ~Scheduler();

        void add_task(const std::function<void()> &task);

    protected:
        std::function<void()> Task;
        std::vector<std::thread> workers;
        std::queue<std::function<void()> > tasks;
        std::mutex queueMutex;
        std::condition_variable condition;
        bool stop;
    };


#endif //SCHEDULER_H
}

