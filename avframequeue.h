/******************************************************************************
 * Copyright 2020-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       avframequeue.h
 * @brief      AVFrameQueue Function
 *
 * @author     FlixTom<2766314754@qq.com>
 * @date       2024/12/17
 * @history
 *****************************************************************************/
#ifndef AVFRAMEQUEUE_H
#define AVFRAMEQUEUE_H
#include "queue.h"

#ifdef __cplusplus  ///
extern "C"
{
// 包含ffmpeg头文件
//#include "libavutil/avutil.h"
//#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
}
#endif

class AVFrameQueue
{
public:
    AVFrameQueue();
    ~AVFrameQueue();

    void Abort();
    int Push(AVFrame *val);
    AVFrame *Pop(const int timeout);
    AVFrame *Front();
    int Size();
private:
    void release();
    Queue<AVFrame *> queue_;

};

#endif // AVFRAMEQUEUE_H
