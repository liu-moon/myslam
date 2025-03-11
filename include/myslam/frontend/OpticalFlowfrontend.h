#pragma once

#include <myslam/map/map.h>

#include "myslam/common/common_include.h"
#include "myslam/frontend/frontend_base.h"
#include "myslam/camera/Pinholecamera.h"

namespace myslam {
    class OpticalFlowfrontend : public FrontendBase {
    private:
        cv::Ptr<cv::GFTTDetector> gftt_;
        Pinholecamera::Ptr camera_left_ = nullptr;
        Pinholecamera::Ptr camera_right_ = nullptr;


    public:
        Map::Ptr map_;
        OpticalFlowfrontend(int num_features = 500);

        OpticalFlowfrontend(Map::Ptr map, int num_features = 500);

        void DetectFeature(Frame::Ptr frame) override;

        void FindFeatureInRight(Frame::Ptr frame) override;

        void SetLeftCamera(Pinholecamera::Ptr camera_left);

        void SetRightCamera(Pinholecamera::Ptr camera_right);

        void SetCameras(Pinholecamera::Ptr camera_left, Pinholecamera::Ptr camera_right);

        bool BuildInitMap(Frame::Ptr frame);
    };
}
