/******************************************************************************
 * Copyright 2020-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       decodethread.h
 * @brief      DecodeThread Function
 *
 * @author     FlixTom<2766314754@qq.com>
 * @date       2024/12/17
 * @history
 *****************************************************************************/
#ifndef DECODETHREAD_H
#define DECODETHREAD_H
#include "thread.h"
#include "avpacketqueue.h"
#include "avframequeue.h"

class DecodeThread:public Thread
{
public:
    DecodeThread(AVPacketQueue *packet_queue, AVFrameQueue *frame_queue);
    ~DecodeThread();

    int Init(AVCodecParameters *par);
    int Start();
    int Stop();
    void Run();
private:
    char err2str[256] = {0};
    AVCodecContext * codec_ctx_ = NULL;
    AVPacketQueue *packet_queue_ = NULL;
    AVFrameQueue *frame_queue_ = NULL;
};

#endif // DECODETHREAD_H
