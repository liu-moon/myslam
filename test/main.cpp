#include <opencv2/opencv.hpp>
#include <iostream>
#include "myslam/frontend/ORBfrontend.h"
#include "myslam/common/viewer.h"

using namespace myslam;

int main() {
    // 创建一帧图像
    Frame::Ptr frame = std::make_shared<Frame>();
    frame->image_ = cv::imread("/home/liuiu/下载/data_odometry_gray/dataset/sequences/00/image_0/000000.png", cv::IMREAD_GRAYSCALE);

    if (frame->image_.empty()) {
        std::cerr << "Failed to load image!" << std::endl;
        return -1;
    }

    // 创建 ORB 前端
    ORBFrontend frontend(500);

    // 检测特征点
    frontend.DetectFeature(frame);

    // 输出特征点数量
    std::cout << "Detected " << frame->features_.size() << " features." << std::endl;

    // 创建Viewer
    if (frame->image_.empty()) {
        std::cerr << "Failed to load image!" << std::endl;
        return -1;
    }
    Viewer::Ptr viewer = std::make_shared<Viewer>();
    viewer->DisplayKeypoints(frame);


    return 0;
}
