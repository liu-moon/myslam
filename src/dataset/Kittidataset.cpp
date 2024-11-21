#include "myslam/dataset/Kittidataset.h"
#include <fstream>


namespace myslam {
    KittiDataset::KittiDataset(const std::string &dataset_path) : dataset_path_(dataset_path){};

    bool KittiDataset::Init() {
        std::ifstream fin(dataset_path_ + "/calib.txt");
        if (!fin) {
            LOG(ERROR) << "cannot find " << dataset_path_ << "/calib.txt!";
            return false;
        }

        for (int i = 0; i < 4; ++i) {
            char camera_name[3];
            for (int k = 0; k < 3; ++k) {   // 读取名称
                fin >> camera_name[k];
                LOG(INFO) << camera_name[k];
            }
            double projection_data[12];
            for (int k = 0; k < 12; ++k) {
                fin >> projection_data[k];
            }
            Mat33 K;
            K << projection_data[0], projection_data[1], projection_data[2],
                projection_data[4], projection_data[5], projection_data[6],
                projection_data[8], projection_data[9], projection_data[10];
            LOG(INFO) << "K = " << std::endl << K << std::endl;
            Vec3 t;
            t << projection_data[3], projection_data[7], projection_data[11];
            LOG(INFO) << "t = " << std::endl << t << std::endl;
            t = K.inverse() * t;    // 平移量转换到相机坐标系
            LOG(INFO) << "t = " << std::endl << t << std::endl;
            K = K * 0.5;
            LOG(INFO) << "K = " << std::endl << K << std::endl;

            Pinholecamera::Ptr new_camera(new Pinholecamera(K(0, 0), K(1, 1), K(0, 2), K(1, 2),
            t.norm(), SE3(SO3(), t)));
            cameras_.push_back(new_camera);
            LOG(INFO) << "Camera " << i << " extrinsics: " << t.transpose();
        }
        fin.close();
        return true;
    };
}