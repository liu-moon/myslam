#include "myslam/common/viewer.h"

namespace myslam
{
    void Viewer::DisplayKeypoints(const Frame::Ptr frame, bool show_left)
    {
        cv::Mat output_image;

        if (show_left) {
            // 处理左图
            cv::cvtColor(frame->left_img_, output_image, cv::COLOR_BGR2RGB);
            for (size_t i = 0; i < frame->features_left_.size(); i++) {
                auto feat = frame->features_left_[i];
                cv::circle(output_image, feat->position_.pt, 2, cv::Scalar(0, 255, 0), 2);
            }
        } else {
            // 处理右图
            cv::cvtColor(frame->right_img_, output_image, cv::COLOR_BGR2RGB);
            for (size_t i = 0; i < frame->features_right_.size(); i++) {
                auto feat = frame->features_right_[i];
                if (feat) { // 确保特征点非空
                    cv::circle(output_image, feat->position_.pt, 2, cv::Scalar(255, 0, 0), 2);
                }
            }
        }

        // 显示图像
        cv::imshow(show_left ? "Left Image" : "Right Image", output_image);
        cv::waitKey(0); // 等待按键关闭窗口
    }

}