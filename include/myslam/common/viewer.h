#pragma once

#include "myslam/common/common_include.h"
#include "myslam/common/frame.h"

namespace myslam
{
    class Viewer
    {
    public:
        typedef std::shared_ptr<Viewer> Ptr;
        Viewer() {};

        void DisplayKeypoints(const Frame::Ptr frame, bool show_left = true);
        void DrawFeatureMatches(const cv::Mat& img_left, const cv::Mat& img_right,
                        const std::vector<cv::Point2f>& kps_left,
                        const std::vector<cv::Point2f>& kps_right,
                        const std::vector<uchar>& status);
    };
}