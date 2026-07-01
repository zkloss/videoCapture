#include "ffvideoadapter.h"

FFVideoAdapter::FFVideoAdapter()
{

}

FFVideoAdapter::~FFVideoAdapter()
{
    if(sws_ctx){
        sws_free_context(&sws_ctx);
    }
}

void FFVideoAdapter::initSws(int width, int height)
{
    if(sws_ctx){
        sws_free_context(&sws_ctx);
    }
    sws_ctx = sws_getContext(
                width, height, AV_PIX_FMT_BGR24,
                width, height, AV_PIX_FMT_YUV420P,
                SWS_FAST_BILINEAR, nullptr, nullptr, nullptr
                );

    lastW = width;
    lastH = height;

    if (!sws_ctx) {
        std::cerr << "Error: Could not initialize SwsContext!" << std::endl;
        return;
    }
}


AVFrame *FFVideoAdapter::convertMatToFrame(const cv::Mat& bgrMat)
{
    AVFrame* frame = av_frame_alloc();
    if (!frame) {
        std::cerr << "Error: Could not allocate video frame!" << std::endl;
        return nullptr;
    }

    int width = bgrMat.cols;
    int height = bgrMat.rows;
    frame->format = AV_PIX_FMT_YUV420P;
    frame->width = width;
    frame->height = height;

    int ret = av_frame_get_buffer(frame, 0);
    if (ret < 0) {
        std::cerr << "Error: Could not allocate the video frame data!" << std::endl;
        av_frame_free(&frame);
        return nullptr;
    }

    int bgrLinesize[1] = { static_cast<int>(bgrMat.step) };
    const uint8_t* bgrData[1] = { bgrMat.data };

    if(sws_ctx == nullptr || lastW != width ||lastH != height){
        initSws(width,height);
    }
    sws_scale(
                sws_ctx, bgrData, bgrLinesize, 0, height,
                frame->data, frame->linesize
                );


    return frame;
}

cv::Mat FFVideoAdapter::convertFrameToMat(AVFrame *frame)
{
    int width = frame->width;
    int height = frame->height;


    cv::Mat yuvMat(height * 3 / 2, width, CV_8UC1);

    memcpy(yuvMat.data, frame->data[0], width * height);
    memcpy(yuvMat.data + width * height, frame->data[1], width * height / 4);
    memcpy(yuvMat.data + width * height * 5 / 4, frame->data[2], width * height / 4);

    cv::Mat bgrMat;
    cv::cvtColor(yuvMat, bgrMat, cv::COLOR_YUV2BGR_I420);

    return bgrMat;
}


