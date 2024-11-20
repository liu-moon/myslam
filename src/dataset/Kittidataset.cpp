#include "myslam/dataset/Kittidataset.h"
#include <fstream>



namespace myslam {
    KittiDataset::KittiDataset(const std::string &dataset_path) : dataset_path_(dataset_path){};

    bool KittiDataset::Init() {
        std::ifstream fin(dataset_path_ + "/calib.txt");
        if (!fin) {
            // LOG(ERROR) << "cannot find " << dataset_path_ << "/calib.txt!";
            return false;
        }
    };
}