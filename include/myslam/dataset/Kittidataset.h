#pragma once

#include "myslam/common/common_include.h"
#include "myslam/dataset/dataset_base.h"
#include "myslam/camera/Pinholecamera.h"

namespace myslam {
    class KittiDataset : public DatasetBase {
    public:
        typedef std::shared_ptr<KittiDataset> Ptr;

        KittiDataset(const std::string &dataset_path);

        bool Init() override;

        Pinholecamera::Ptr GetCamera(int camera_id) const {
            return cameras_.at(camera_id);
        };

    private:
        std::string dataset_path_; // 数据集路径
        std::vector<Pinholecamera::Ptr> cameras_; // 相机向量
    };
}
