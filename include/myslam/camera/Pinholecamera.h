#pragma once

#include <memory>

#include "myslam/camera/camera_base.h"
#include "myslam/common/common_include.h"

namespace myslam {
    class Pinholecamera : public CameraBase {
    public:
        typedef std::shared_ptr<Pinholecamera> Ptr;

        double fx_ = 0, fy_ = 0, cx_ = 0, cy_ = 0,
           baseline_ = 0; // Camera intrinsics
        SE3 pose_;            // extrinsic, from stereo camera to single camera
        Pinholecamera(double fx, double fy, double cx, double cy, double baseline,
           const SE3 &pose);

    };
}