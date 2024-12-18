/******************************************************************************
 * Copyright 2020-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       audiooutput.h
 * @brief      AudioOutput Function
 * use SDL :
 * 1.SDL_Init initialization supports audio
 * 2.SDL_PauseAudio pauses or turns on audio output
 * 3.SDL_OpenAudio sets audio output parameters and callback functions
 *
 * @author     FlixTom<2766314754@qq.com>
 * @date       2024/12/18
 * @history
 *****************************************************************************/
#ifndef AUDIOOUTPUT_H
#define AUDIOOUTPUT_H

#ifdef __cplusplus  ///
extern "C"
{
// 包含ffmpeg头文件
//#include "libavutil/avutil.h"
#include "SDL.h"
#include "libswresample/swresample.h"
}
#endif


#include "avframequeue.h"
typedef struct AudioParams
{
    int freq;//采样率
    int channels;
    int64_t channel_layout;
    enum AVSampleFormat fmt;
    int frame_Size;
}AudioParams;

class AudioOutput
{
public:
    AudioOutput(const AudioParams &audio_params,AVFrameQueue *frame_queue);
    ~AudioOutput();
    int Init();
    int DeInit();
private:
    AudioParams src_tgt_; //解码后的参数
    AudioParams dst_tgt_; // SDL实际输出的格式
    AVFrameQueue *frame_queue_;

    struct SwrContext *swr_ctx_ = NULL;

    uint8_t *audio_buf_ = NULL;
    uint8_t *audio_buf1_ = NULL;
    uint32_t audio_buf_size =0;
    uint32_t audio_buf1_size =0;
    uint32_t audio_buf_index =0;
};

#endif // AUDIOOUTPUT_H
