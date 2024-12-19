/******************************************************************************
 * Copyright 2020-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       videooutput.h
 * @brief      VideoOutput Function
 *
 * @author     FlixTom<2766314754@qq.com>
 * @date       2024/12/19
 * @history
 *****************************************************************************/
#ifndef VIDEOOUTPUT_H
#define VIDEOOUTPUT_H

#ifdef __cplusplus  ///
extern "C"
{
// 包含ffmpeg头文件
//#include "libavutil/avutil.h"
#include "SDL.h"
}
#endif

#include "avframequeue.h"

class VideoOutput
{
public:
    VideoOutput(AVFrameQueue *frame_queue, int video_width, int video_height);
    ~VideoOutput();
    int Init();
    int MainLoop();
    void RefreshLoopWaitEvent(SDL_Event *event);
private:
    void videoRefresh(double *remaining_time);
    AVFrameQueue * frame_queue_ = NULL;
    SDL_Event event_;
    SDL_Rect rect_;
    SDL_Window *win_ = NULL;
    SDL_Renderer *renderer_ = NULL;
    SDL_Texture *texture_ = NULL;

    int video_width_ = 0;
    int video_height_ = 0;
    uint8_t *yuv_buf_ = NULL;
    int      yuv_buf_size_ = 0;

    /**
     *    VideoOutput
     *    ├── frame_queue_      (存储解码后的视频帧队列)
     *    ├── event_            (SDL 事件对象)
     *    ├── rect_             (渲染区域的矩形)
     *    ├── win_              (SDL 窗口)
     *    ├── renderer_         (SDL 渲染器)
     *    ├── texture_          (SDL 纹理)
     *    ├── video_width_      (视频宽度)
     *    ├── video_height_     (视频高度)
     *    ├── yuv_buf_          (YUV 数据缓冲区)
     *    └── yuv_buf_size_     (YUV 缓冲区大小)
     */
};

#endif // VIDEOOUTPUT_H
