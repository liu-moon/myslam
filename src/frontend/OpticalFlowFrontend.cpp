#include "myslam/frontend/OpticalFlowFrontend.h"

namespace myslam {
    OpticalFlowFrontend::OpticalFlowFrontend(int num_features) {
        int max_corners = num_features;          // 最大角点数量
        double quality_level = 0.01;    // 角点质量阈值
        double min_distance = 20;       // 最小角点间距
        bool use_harris_detector = false; // 是否使用 Harris 检测器
        double k = 0.04;                 // Harris 检测器的参数（如果启用）
        gftt_ = cv::GFTTDetector::create(max_corners, quality_level, min_distance, 3, use_harris_detector, k);
    }

    void OpticalFlowFrontend::DetectFeature(Frame::Ptr frame) {
        std::vector<cv::KeyPoint> keypoints;
        gftt_->detect(frame->left_img_,keypoints);
        for (auto &kp : keypoints) {
            frame->features_.push_back(Feature::Ptr(new Feature(frame,kp)));
        }
    }


}