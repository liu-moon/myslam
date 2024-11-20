#pragma once

#include "myslam/common/common_include.h"
#include "myslam/common/frame.h"

namespace myslam{
    class FrontendBase{
        public:
        virtual void DetectFeature(Frame::Ptr frame) = 0;
        virtual void FindFeatureInRight(Frame::Ptr frame) = 0;
        virtual ~FrontendBase() = default;
    };
}
