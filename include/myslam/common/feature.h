#pragma once

#include "myslam/common/common_include.h"
#include "myslam/map/mappoint.h"

namespace myslam
{
    struct Frame;
    struct MapPoint;

    /**
     * @brief 特征点类
     *
     */
    struct Feature
    {
        typedef std::shared_ptr<Feature> Ptr;
        std::weak_ptr<Frame> frame_; // 持有该 feature 的 frame
        cv::KeyPoint position_;      // 特征点在图像中的位置
        std::weak_ptr<MapPoint> map_point_;  // 关联地图点

        Feature() = default;
        Feature(std::shared_ptr<Frame> frame, const cv::KeyPoint &kp) : frame_(frame), position_(kp) {}
    };
}
