#include "myslam/frontend/OpticalFlowFrontend.h"

namespace myslam
{
    OpticalFlowFrontend::OpticalFlowFrontend(int num_features)
    {
        int max_corners = num_features;   // 最大角点数量
        double quality_level = 0.01;      // 角点质量阈值
        double min_distance = 20;         // 最小角点间距
        bool use_harris_detector = false; // 是否使用 Harris 检测器
        double k = 0.04;                  // Harris 检测器的参数（如果启用）
        gftt_ = cv::GFTTDetector::create(max_corners, quality_level, min_distance, 3, use_harris_detector, k);
    }

    void OpticalFlowFrontend::DetectFeature(Frame::Ptr frame)
    {
        std::vector<cv::KeyPoint> keypoints;
        gftt_->detect(frame->left_img_, keypoints);
        for (auto &kp : keypoints)
        {
            frame->features_left_.push_back(Feature::Ptr(new Feature(frame, kp)));
        }
    }

    void OpticalFlowFrontend::FindFeatureInRight(Frame::Ptr frame)
    {
        std::vector<cv::Point2f> kps_left, kps_right;
        for (auto &kp : frame->features_left_) // 遍历左图特征点
        {
            kps_left.push_back(kp->position_.pt); // kps_left添加特征点

            // use same pixel in left iamge
            kps_right.push_back(kp->position_.pt); // 没有投影点的情况下，直接使用左图的特征点
        }

        std::vector<uchar> status;
        cv::Mat error;
        cv::calcOpticalFlowPyrLK(frame->left_img_, frame->right_img_,
                                 kps_left, kps_right, status, error,
                                 cv::Size(11, 11), 3,
                                 cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS, 30, 0.01),
                                 cv::OPTFLOW_USE_INITIAL_FLOW);

        for (size_t i = 0; i < status.size(); ++i)
        {
            if (status[i]) // 跟踪成功
            {
                cv::KeyPoint kp(kps_right[i], 7);          // 7 特征点的邻域大小 经验值
                Feature::Ptr feat(new Feature(frame, kp)); // 创建2D特征点

                frame->features_right_.push_back(feat); // 添加到右图特征
            }
            else // 跟踪失败
            {
                frame->features_right_.push_back(nullptr); // 插入空指针 表示跟踪失败
            }
        }
    }

}