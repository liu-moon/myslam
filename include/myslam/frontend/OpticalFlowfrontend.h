#pragma once

#include "myslam/common/common_include.h"
#include "myslam/frontend/frontend_base.h"

namespace myslam
{
    class OpticalFlowfrontend : public FrontendBase
    {
    private:
        cv::Ptr<cv::GFTTDetector> gftt_;

    public:
        OpticalFlowfrontend(int num_features = 500);
        void DetectFeature(Frame::Ptr frame) override;
        void FindFeatureInRight(Frame::Ptr frame) override;
    };
}