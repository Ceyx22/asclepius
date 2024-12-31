//
// Created by ceyx on 12/30/24.
//

#include "Scheduler.h"

namespace util {
    Scheduler::Scheduler(const size_t threadCount) : stop(false) {
        for (size_t i = 0; i < threadCount; ++i) {
            workers.emplace_back([this]() {
                while (true) {
                    std::function<void()> task; {
                        std::unique_lock<std::mutex> lock(queueMutex);
                        condition.wait(lock, [this]() { return stop || !tasks.empty(); });
                        if (stop && tasks.empty()) return;
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    Scheduler::~Scheduler() { {
            std::unique_lock<std::mutex> lock(queueMutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread &worker: workers) {
            worker.join();
        }
    }

    void Scheduler::add_task(const std::function<void()> &task) { {
            std::unique_lock<std::mutex> lock(queueMutex);
            tasks.push(task);
        }
        condition.notify_one();
    }
}

