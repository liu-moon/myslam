#pragma once

#include "myslam/common/common_include.h"
#include "myslam/common/frame.h"

namespace myslam
{
    class Viewer
    {
    public:
        typedef std::shared_ptr<Viewer> Ptr;
        Viewer() {};

        void DisplayKeypoints(const Frame::Ptr frame, bool show_left = true);
    };
}