#pragma once

#include "myslam/common/common_include.h"
#include "myslam/common/feature.h"

namespace myslam{
    struct Frame{
        typedef std::shared_ptr<Frame> Ptr;

        unsigned long id_ = 0;
        cv::Mat image_;
        std::vector<std::shared_ptr<Feature>> features_;

        Frame() = default;
    };
}