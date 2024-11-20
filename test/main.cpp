#include <opencv2/opencv.hpp>
#include <iostream>
#include "myslam/frontend/ORBfrontend.h"
#include "myslam/common/viewer.h"
#include "myslam/frontend/OpticalFlowFrontend.h"

using namespace myslam;

int main() {
    // 创建一帧图像
    Frame::Ptr frame = std::make_shared<Frame>();
    frame->left_img_ = cv::imread("/home/liuiu/下载/data_odometry_gray/dataset/sequences/00/image_0/000000.png", cv::IMREAD_GRAYSCALE);

    if (frame->left_img_.empty()) {
        std::cerr << "Failed to load image!" << std::endl;
        return -1;
    }

    // 创建 ORB 前端
    ORBFrontend ORBfrontend(500);
    // 检测特征点
    ORBfrontend.DetectFeature(frame);

    // 创建 光流 前端
    OpticalFlowFrontend OpticalFlowfrontend(150);
    Frame::Ptr frame2 = std::make_shared<Frame>();
    frame2->left_img_ = frame->left_img_;

    OpticalFlowfrontend.DetectFeature(frame2);

    std::cout << "Detected features: " << frame2->features_.size() << std::endl;

    // 输出特征点数量
    std::cout << "Detected " << frame->features_.size() << " features." << std::endl;

    Viewer::Ptr viewer = std::make_shared<Viewer>();
    viewer->DisplayKeypoints(frame);

    viewer->DisplayKeypoints(frame2);


    return 0;
}
