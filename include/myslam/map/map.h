#pragma once

#include "myslam/common/common_include.h"
#include "myslam/map/mappoint.h"

namespace myslam {
    class Map {
        public:
        typedef std::shared_ptr<Map> Ptr;
        typedef std::unordered_map<unsigned long, MapPoint::Ptr> LandmarksType;
        Map(){};

        void InsertMapPoint(MapPoint::Ptr map_point);
    private:
        LandmarksType landmarks_;        // all landmarks
        LandmarksType active_landmarks_; // active landmarks
    };
}