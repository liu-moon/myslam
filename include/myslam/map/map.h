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

        /// 获取激活地图点
        LandmarksType GetActiveMapPoints()
        {
            // std::unique_lock<std::mutex> lck(data_mutex_);
            return active_landmarks_;
        }
    private:
        LandmarksType landmarks_;        // all landmarks
        LandmarksType active_landmarks_; // active landmarks
        std::mutex data_mutex_;
    };
}