/******************************************************************************
 * Copyright 2020-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       queue.h
 * @brief      Queue Function
 *
 * @author     FlixTom<2766314754@qq.com>
 * @date       2024/12/17
 * @history
 *****************************************************************************/
#ifndef QUEUE_H
#define QUEUE_H
#include <mutex>
#include <condition_variable>
#include <queue>

template <typename T>
class Queue
{
public:
    Queue() {}
    ~ Queue() {}
    void Abort() {
        abort_ = 1;
        cond_.notify_all();
    }
    /**
     * @brief Push a value to the queue
     *
     * This function pushes a value to the queue. It locks the mutex to ensure thread-safety
     * and checks if the abort flag is set to 1 (indicating that the operation should be aborted).
     * If abort is not set, it pushes the value to the queue and notifies one waiting thread, if any.
     *
     * @param val The value to be pushed to the queue
     * @return int Returns 0 on success, -1 if the operation is aborted
     */
    int Push(T val) {
        std::lock_guard<std::mutex> lock(mutex_);
        if(1 == abort_) {
            return -1;
        }
        queue_.push(val);
        cond_.notify_one();
        return 0;
    }
    /**
     * @brief Pop
     * @param val
     * @param timeout
     * @return
     */
    int Pop(T &val, const int timeout = 0) {
        std::unique_lock<std::mutex> lock(mutex_);
        if(queue_.empty()) {
            // 等待push或者超时唤醒
            cond_.wait_for(lock, std::chrono::milliseconds(timeout), [this] {
                return !queue_.empty() | abort_;
            });
        }
        if(1 == abort_) {
            return -1;
        }
        if(queue_.empty()) {
            return -2;
        }
        val = queue_.front();
        queue_.pop();
        return 0;
    }

    int Front(T &val) {
        std::lock_guard<std::mutex> lock(mutex_);
        if(1 == abort_) {
            return -1;
        }
        if(queue_.empty()) {
            return -2;
        }
        val = queue_.front();
        return 0;
    }

    int Size() {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    }


private:
    int abort_ = 0;
    std::mutex mutex_;
    std::condition_variable cond_;
    std::queue<T> queue_;
};

#endif // QUEUE_H
