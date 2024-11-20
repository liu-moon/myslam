#include "myslam/common/viewer.h"

namespace myslam
{
    void Viewer::DisplayKeypoints(const Frame::Ptr frame)
    {
        cv::Mat output_image;
        cv::cvtColor(frame->image_, output_image, cv::COLOR_BGR2RGB);
        for(size_t i = 0; i < frame->features_.size();i++) {
            auto feat = frame->features_[i];
            cv::circle(output_image,feat->position_.pt,2,cv::Scalar(0,255,0),2);
        }

        // 显示图像
        cv::imshow("image", output_image);
        cv::waitKey(0); // 等待按键关闭窗口
    }
}