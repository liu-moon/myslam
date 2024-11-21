#pragma once

#include <opencv2/features2d.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <glog/logging.h>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <sophus/se3.hpp>
#include <sophus/so3.hpp>

typedef Sophus::SE3d SE3;
typedef Sophus::SO3d SO3;

typedef Eigen::Matrix<double, 3, 3> Mat33;
typedef Eigen::Matrix<double, 3, 1> Vec3;
