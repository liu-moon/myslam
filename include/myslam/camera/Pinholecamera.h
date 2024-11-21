#pragma once

#include <memory>

#include "myslam/camera/camera_base.h"
#include "myslam/common/common_include.h"

namespace myslam {
    class Pinholecamera : public CameraBase {
    public:
        typedef std::shared_ptr<Pinholecamera> Ptr;

        Pinholecamera(double fx, double fy, double cx, double cy, double baseline,
                      const SE3 &pose);

        SE3 pose() const { return pose_; };

        Vec3 pixelToCam(const Vec2 &p_p, double depth = 1);
    private:
        double fx_ = 0, fy_ = 0, cx_ = 0, cy_ = 0,
                baseline_ = 0; // Camera intrinsics
        SE3 pose_; // extrinsic, from stereo camera to single camera
    };
}
