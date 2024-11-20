
    
#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <iostream>
#include <string>

int main() {
    std::string path = "/home/liuiu/下载/data_odometry_gray/dataset/sequences/00/image_0/000000.png";
    // 读取输入图像
    std::string image_path = path;
    cv::Mat image = cv::imread(image_path);
    if (image.empty()) {
        std::cerr << "无法读取图像！" << std::endl;
        return -1;
    }

    // 转换为灰度图
    cv::Mat gray_image;
    cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);

    // 创建 GFTTDetector
    int max_corners = 100;          // 最大角点数量
    double quality_level = 0.01;    // 角点质量阈值
    double min_distance = 10;       // 最小角点间距
    bool use_harris_detector = false; // 是否使用 Harris 检测器
    double k = 0.04;                 // Harris 检测器的参数（如果启用）

    auto gftt = cv::GFTTDetector::create(max_corners, quality_level, min_distance, 3, use_harris_detector, k);

    // 检测关键点
    std::vector<cv::KeyPoint> keypoints;
    gftt->detect(gray_image, keypoints);

    // 在图像上绘制关键点
    cv::Mat output_image;
    cv::drawKeypoints(image, keypoints, output_image, cv::Scalar(0, 0, 255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    // 显示结果
    cv::imshow("GFTT Keypoints", output_image);
    cv::waitKey(0);

    return 0;
}
    