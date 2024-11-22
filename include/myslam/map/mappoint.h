#pragma once

#include "myslam/common/common_include.h"
#include "myslam/common/feature.h"

namespace myslam {
    struct Feature; // 前向声明
    struct MapPoint {
        typedef std::shared_ptr<MapPoint> Ptr;
        unsigned long id_ = 0; // 地图点id
        int observed_times_ = 0;  // 地图点被观测到的次数

        std::mutex data_mutex_;    // 数据锁

        Vec3 pos_ = Vec3::Zero(); // Position in world 世界坐标系中位置

        std::list<std::weak_ptr<Feature>> observations_;    // 该地图点被哪些特征观测

        void SetPos(const Vec3 &pos) {
            // 设置三维坐标
            std::unique_lock<std::mutex> lck(data_mutex_); // 函数退出自动解锁
            pos_ = pos;
        };

        void AddObservation(std::shared_ptr<Feature> feature) {
            // 添加观测
            std::unique_lock<std::mutex> lck(data_mutex_);
            observations_.push_back(feature);
            observed_times_++;
        }

        // factory function
        static Ptr CreateNewMappoint();
    };
}
