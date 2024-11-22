#include "myslam/map/map.h"

namespace myslam {
    void Map::InsertMapPoint(MapPoint::Ptr map_point)
    {
        if (landmarks_.find(map_point->id_) == landmarks_.end())
        {                                                                   // 检查地图点是否已经存在
            landmarks_.insert(make_pair(map_point->id_, map_point));        // 插入新地图点
            active_landmarks_.insert(make_pair(map_point->id_, map_point)); // 插入激活地图点
        }
        else // 已经存在 说明某些信息可能发生了变化
        {
            landmarks_[map_point->id_] = map_point;        // 更新已有的地图点
            active_landmarks_[map_point->id_] = map_point; // 激活地图点
        }
    }
}