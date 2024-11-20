#pragma once

#include "myslam/common/common_include.h"

namespace myslam {
    class DatasetBase {
        public:
            DatasetBase() {};
            virtual bool Init() = 0;
    };
}