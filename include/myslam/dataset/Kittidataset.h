#pragma once

#include "myslam/common/common_include.h"
#include "myslam/dataset/dataset_base.h"

namespace myslam {
    class KittiDataset : public DatasetBase {
        public:

        typedef std::shared_ptr<KittiDataset> Ptr;
        KittiDataset(const std::string &dataset_path);
        bool Init() override;

    private:
        std::string dataset_path_;
    };
}