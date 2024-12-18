/******************************************************************************
 * Copyright 2020-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       thread.h
 * @brief      Thread Function
 *
 * @author     FlixTom<2766314754@qq.com>
 * @date       2024/12/17
 * @history
 *****************************************************************************/
#ifndef THREAD_H
#define THREAD_H

#include <thread>

class Thread
{
public:
    Thread() {}
    ~Thread() {
        if(thread_) {
            Thread::Stop();
        }
    }
    int Start() {}
    int Stop() {
        abort_ = 1;
        if(thread_) {
            thread_->join();
            delete thread_;
            thread_ = NULL;
        }
    }
    virtual void Run() = 0;
protected:
    int abort_ = 0;
    std::thread *thread_ = NULL;
};

#endif // THREAD_H
