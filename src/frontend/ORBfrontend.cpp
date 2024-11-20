#include "myslam/frontend/ORBfrontend.h"

namespace myslam
{
    // 构造函数的实现
    ORBFrontend::ORBFrontend(int num_features)
    {
        orb_ = cv::ORB::create(num_features); // 初始化 ORB 检测器
    }

    // DetectFeatures 的实现
    void ORBFrontend::DetectFeature(Frame::Ptr frame)
    {
        std::vector<cv::KeyPoint> keypoints;
        cv::Mat descriptors;

        // 检测特征点
        orb_->detectAndCompute(frame->left_img_, cv::noArray(), keypoints, descriptors);

        // 将检测到的特征点存储到 Frame 的 features_ 中
        for (const auto &kp : keypoints)
        {
            auto feature = std::make_shared<Feature>();
            feature->position_ = kp;
            feature->frame_ = frame;
            frame->features_left_.push_back(feature);
        }
    }
}