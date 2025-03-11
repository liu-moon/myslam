#pragma once

#include "myslam/common/common_include.h"
#include "myslam/common/frame.h"
#include <pangolin/pangolin.h>
#include "myslam/map/mappoint.h"
#include "myslam/map/map.h"

namespace myslam {
    class Viewer {
    public:
        typedef std::shared_ptr<Viewer> Ptr;

        Viewer() {
        };

        void SetMap(Map::Ptr map) { map_ = map; }

        void DisplayKeypoints(const Frame::Ptr frame, bool show_left = true);

        void DrawFeatureMatches(const cv::Mat &img_left, const cv::Mat &img_right,
                                const std::vector<cv::Point2f> &kps_left,
                                const std::vector<cv::Point2f> &kps_right,
                                const std::vector<uchar> &status);

        void DrawMapPoints();

        void ThreadLoop();

        void UpdateMap();

    private:
        std::unordered_map<unsigned long, Frame::Ptr> active_keyframes_;

        std::unordered_map<unsigned long, MapPoint::Ptr> active_landmarks_;

        Map::Ptr map_ = nullptr;
    };
}
