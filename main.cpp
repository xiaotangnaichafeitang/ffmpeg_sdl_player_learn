/******************************************************************************
 * Copyright 2020-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       main.cpp
 * @brief      main Function
 *
 * @author     FlixTom<2766314754@qq.com>
 * @date       2024/12/17
 * @history
 *****************************************************************************/
#include <iostream>
#include "log.h"
#include "demuxthread.h"
#include "avframequeue.h"
#include "decodethread.h"
using namespace std;

int main(int argc, char *argv[])
{
    int ret = 0;
    cout << "Hello World!" << endl;
    LogInit();
    // queue
    AVPacketQueue audio_packet_queue;
    AVPacketQueue video_packet_queue;

    AVFrameQueue audio_frame_queue;
    AVFrameQueue video_frame_queue;
    //1 .解复用
    DemuxThread *demux_thread = new DemuxThread(&audio_packet_queue, &video_packet_queue);
    ret = demux_thread->Init(argv[1]);
    if(ret < 0) {
        LogError("demux_thread.Init failed");
        return -1;
    }

    ret = demux_thread->Start();
    if(ret < 0) {
        LogError("demux_thread.Start() failed");
        return -1;
    }
    //解码线程初始化
    DecodeThread *audio_decode_thread = new DecodeThread(&audio_packet_queue, &audio_frame_queue );
    ret = audio_decode_thread->Init(demux_thread->AudioCodeParameters());
    if(ret < 0) {
        LogError("audio_decode_thread->Init failed");
        return -1;
    }
    ret = audio_decode_thread->Start();
    if(ret < 0) {
        LogError("audio_decode_thread->Start failed");
        return -1;
    }

    DecodeThread *video_decode_thread = new DecodeThread(&video_packet_queue, &video_frame_queue );
    ret = video_decode_thread->Init(demux_thread->VideoCodeParameters());
    if(ret < 0) {
        LogError("audio_decode_thread->Init failed");
        return -1;
    }
    ret = video_decode_thread->Start();
    if(ret < 0) {
        LogError("audio_decode_thread->Start failed");
        return -1;
    }

    // 休眠2秒
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    LogInfo("demux_thread->Stop");
    demux_thread->Stop();
    LogInfo("delete demux_thread");
    delete demux_thread;

    LogInfo("audio_decode_thread->Stop()");
    audio_decode_thread->Stop();
    LogInfo("delete audio_decode_thread");
    delete audio_decode_thread;

    LogInfo("main finish");

    return 0;
}
