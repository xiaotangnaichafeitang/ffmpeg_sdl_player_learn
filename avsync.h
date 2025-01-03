﻿/******************************************************************************
 * Copyright 2020-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       avsync.h
 * @brief      AVSync Function
 *
 * @author     FlixTom<2766314754@qq.com>
 * @date       2024/12/20
 * @history
 *****************************************************************************/
#ifndef AVSYNC_H
#define AVSYNC_H

#include <chrono>
#include <ctime>
#include <math.h>
using namespace std::chrono;


class AVSync
{
public:
    AVSync(){}
    void InitClock(){
        SetClock(NAN);
    }

    void SetClockAt(double pts, double time){
        pts_ = pts;
        pts_drift_ = pts_ - time ;
    }

    double GetClock(){
        double time = GetMicroseconds() / 1000000.0; // us -> s
        return pts_drift_ + time;
    }

    void SetClock(double pts){
        double time = GetMicroseconds() / 1000000.0; // us -> s
        SetClockAt(pts , time);
    }

    time_t GetMicroseconds(){
        system_clock::time_point time_point_new = system_clock::now();  // 时间一直动
        system_clock::duration duration = time_point_new.time_since_epoch();

        time_t us = duration_cast<microseconds>(duration).count();
        return us;
    }

    double pts_ = 0;
    double pts_drift_ = 0;
};

#endif // AVSYNC_H
