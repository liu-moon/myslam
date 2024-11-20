#pragma once

#include "myslam/common/common_include.h"
#include "myslam/common/feature.h"

namespace myslam
{
    struct Frame
    {
        typedef std::shared_ptr<Frame> Ptr;

        cv::Mat left_img_, right_img_;
        std::vector<std::shared_ptr<Feature>> features_left_;
        std::vector<std::shared_ptr<Feature>> features_right_;

        Frame() = default;
    };
}