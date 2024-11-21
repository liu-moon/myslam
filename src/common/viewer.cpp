#include "myslam/common/viewer.h"

namespace myslam
{
    void Viewer::DisplayKeypoints(const Frame::Ptr frame, bool show_left)
    {
        cv::Mat output_image;

        if (show_left)
        {
            // 处理左图
            cv::cvtColor(frame->left_img_, output_image, cv::COLOR_BGR2RGB);
            for (size_t i = 0; i < frame->features_left_.size(); i++)
            {
                auto feat = frame->features_left_[i];
                cv::circle(output_image, feat->position_.pt, 2, cv::Scalar(0, 255, 0), 2);
            }
        }
        else
        {
            // 处理右图
            cv::cvtColor(frame->right_img_, output_image, cv::COLOR_BGR2RGB);
            for (size_t i = 0; i < frame->features_right_.size(); i++)
            {
                auto feat = frame->features_right_[i];
                if (feat)
                { // 确保特征点非空
                    cv::circle(output_image, feat->position_.pt, 2, cv::Scalar(255, 0, 0), 2);
                }
            }
        }

        // 显示图像
        cv::imshow(show_left ? "Left Image" : "Right Image", output_image);
        cv::waitKey(0); // 等待按键关闭窗口
    }

    void Viewer::DrawFeatureMatches(const cv::Mat &img_left, const cv::Mat &img_right, const std::vector<cv::Point2f> &kps_left, const std::vector<cv::Point2f> &kps_right, const std::vector<uchar> &status) {
        // 创建一张新图，用于拼接左右图像
        cv::Mat img_matches;
        cv::hconcat(img_left, img_right, img_matches); // 将左右图像水平拼接

        // 遍历特征点并绘制连线和点
        for (size_t i = 0; i < kps_left.size(); ++i) {
            if (status[i]) { // 只绘制匹配成功的特征点
                // 左图中的特征点
                cv::Point2f pt_left = kps_left[i];
                // 右图中的特征点，右图的点需要偏移到拼接后的图像右半部分
                cv::Point2f pt_right = kps_right[i] + cv::Point2f((float)img_left.cols, 0);

                // 随机生成颜色
                cv::Scalar color = cv::Scalar(rand() % 255, rand() % 255, rand() % 255);

                // 绘制连线
                cv::line(img_matches, pt_left, pt_right, color, 1, cv::LINE_AA);
                // 绘制特征点
                cv::circle(img_matches, pt_left, 5, color, -1);
                cv::circle(img_matches, pt_right, 5, color, -1);
            }
        }

        // 显示匹配图
        cv::imshow("Feature Matches", img_matches);
        cv::waitKey(0); // 等待用户按键
    }

}