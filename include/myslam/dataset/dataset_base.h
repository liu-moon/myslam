#pragma once

namespace myslam {
    class DatasetBase {
        public:
            DatasetBase() {};
            virtual bool Init() = 0;
    };
}