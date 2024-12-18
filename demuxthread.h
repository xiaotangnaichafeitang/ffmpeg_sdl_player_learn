﻿/******************************************************************************
 * Copyright 2020-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       demuxthread.h
 * @brief      DemuxThread Function
 *
 * @author     FlixTom<2766314754@qq.com>
 * @date       2024/12/17
 * @history
 *****************************************************************************/
#ifndef DEMUXTHREAD_H
#define DEMUXTHREAD_H

#include "thread.h"
#include "avpacketqueue.h"

#ifdef __cplusplus  ///
extern "C"
{
// 包含ffmpeg头文件
#include "libavutil/avutil.h"
#include "libavformat/avformat.h"
}
#endif

class DemuxThread :public Thread
{
public:
    DemuxThread(AVPacketQueue *audio_queue, AVPacketQueue *video_queue);
    ~DemuxThread();
    int Init(const char *url);
    int Start();
    int Stop();
    void Run();

    AVCodecParameters *AudioCodecParameters();
    AVCodecParameters *VideoCodecParameters();

private:
    char err2str[256] = {0};
    std::string url_;//文件名
    AVPacketQueue *audio_queue_ = NULL;
    AVPacketQueue *video_queue_ = NULL;


    AVFormatContext *ifmt_ctx_ = NULL;
    int audio_index_ = -1;
    int video_index_ = -1;
};

#endif // DEMUXTHREAD_H
