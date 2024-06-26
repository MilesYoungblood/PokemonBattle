//
// Created by Miles Youngblood on 4/10/2024.
//

#include "ThreadPool.h"

ThreadPool::~ThreadPool() {
    this->clear();
}

void ThreadPool::init(std::size_t n) {
    // safe clean threads already here in case of re-initialization
    this->clear();
    this->running = true;

    for (std::size_t i = 0; i < n; ++i) {
        this->workers.emplace_back([this] -> void {
            while (true) {
                std::function<void()> task;

                {
                    std::unique_lock lock(this->mutex);
                    this->cv.wait(lock, [this] -> bool { return not this->running or not this->tasks.empty(); });

                    if (not this->running and this->tasks.empty()) {
                        return;
                    }

                    task = std::move(this->tasks.front());
                    this->tasks.pop();
                    ++this->activeThreads;
                }

                task();

                std::scoped_lock lock(this->mutex);
                --this->activeThreads;
                if (this->activeThreads == 0) {
                    this->allIdle.notify_one();
                }
            }
        });
    }
}

void ThreadPool::add(std::function<void()> task) {
    {
        std::scoped_lock lock(this->mutex);
        this->tasks.push(std::move(task));
    }
    this->cv.notify_one();
}

void ThreadPool::block() {
    std::unique_lock lock(this->mutex);
    this->allIdle.wait(lock, [this] -> bool { return this->tasks.empty() and this->activeThreads == 0; });
}

void ThreadPool::clear() {
    this->running = false;
    this->cv.notify_all();

    for (auto &worker : this->workers) {
        worker.join();
    }

    this->workers.clear();
}
