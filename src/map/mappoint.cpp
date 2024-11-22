#include "myslam/map/mappoint.h"

namespace myslam {
    MapPoint::Ptr MapPoint::CreateNewMappoint() {
        static long factory_id = 0;
        MapPoint::Ptr new_mappoint(new MapPoint);
        new_mappoint->id_ = factory_id++;
        return new_mappoint;
    }
}

