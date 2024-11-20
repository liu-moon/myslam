#pragma once

#include "myslam/frontend/frontend_base.h"
#include "myslam/common/common_include.h"

namespace myslam
{
    class ORBFrontend : public FrontendBase
    {
    private:
        cv::Ptr<cv::ORB> orb_;

    public:
        ORBFrontend(int num_features = 500);
        void DetectFeature(Frame::Ptr frame) override;
        void FindFeatureInRight(Frame::Ptr frame) override {};
    };
}