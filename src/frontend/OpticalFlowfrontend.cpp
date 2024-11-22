#include "myslam/frontend/OpticalFlowfrontend.h"
#include <myslam/common/viewer.h>
#include "myslam/common/algorithm.h"

namespace myslam {
    OpticalFlowfrontend::OpticalFlowfrontend(int num_features) {
        int max_corners = num_features; // 最大角点数量
        double quality_level = 0.01; // 角点质量阈值
        double min_distance = 20; // 最小角点间距
        bool use_harris_detector = false; // 是否使用 Harris 检测器
        double k = 0.04; // Harris 检测器的参数（如果启用）
        gftt_ = cv::GFTTDetector::create(max_corners, quality_level, min_distance, 3, use_harris_detector, k);
    }

    void OpticalFlowfrontend::DetectFeature(Frame::Ptr frame) {
        std::vector<cv::KeyPoint> keypoints;
        gftt_->detect(frame->left_img_, keypoints);
        for (auto &kp: keypoints) {
            frame->features_left_.push_back(Feature::Ptr(new Feature(frame, kp)));
        }
    }

    void OpticalFlowfrontend::FindFeatureInRight(Frame::Ptr frame) {
        std::vector<cv::Point2f> kps_left, kps_right;
        for (auto &kp: frame->features_left_) // 遍历左图特征点
        {
            kps_left.push_back(kp->position_.pt); // kps_left添加特征点

            // use same pixel in left iamge
            kps_right.push_back(kp->position_.pt); // 没有投影点的情况下，直接使用左图的特征点
        }

        std::vector<uchar> status;
        cv::Mat error;
        cv::calcOpticalFlowPyrLK(frame->left_img_, frame->right_img_,
                                 kps_left, kps_right, status, error,
                                 cv::Size(11, 11), 3,
                                 cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS, 30, 0.01),
                                 cv::OPTFLOW_USE_INITIAL_FLOW);

        for (size_t i = 0; i < status.size(); ++i) {
            if (status[i]) // 跟踪成功
            {
                cv::KeyPoint kp(kps_right[i], 7); // 7 特征点的邻域大小 经验值
                Feature::Ptr feat(new Feature(frame, kp)); // 创建2D特征点

                frame->features_right_.push_back(feat); // 添加到右图特征
            } else // 跟踪失败
            {
                frame->features_right_.push_back(nullptr); // 插入空指针 表示跟踪失败
            }
        }

        // 调用绘图函数
        // todo 这里放在类外执行
        Viewer::Ptr viewer = std::make_shared<Viewer>();
        viewer->DrawFeatureMatches(frame->left_img_, frame->right_img_, kps_left, kps_right, status);
    }

    void OpticalFlowfrontend::SetLeftCamera(Pinholecamera::Ptr camera_left) {
        camera_left_ = camera_left;
    }

    void OpticalFlowfrontend::SetRightCamera(Pinholecamera::Ptr camera_right) {
        camera_right_ = camera_right;
    }

    void OpticalFlowfrontend::SetCameras(Pinholecamera::Ptr camera_left, Pinholecamera::Ptr camera_right) {
        camera_left_ = camera_left;
        camera_right_ = camera_right;
    }

    bool OpticalFlowfrontend::BuildInitMap(Frame::Ptr frame) {
        std::vector<SE3> poses{camera_left_->pose(), camera_right_->pose()};
        for (size_t i = 0; i < poses.size(); ++i) {
            const auto &pose = poses[i];
            LOG(INFO) << "Pose " << i << ":";
            LOG(INFO) << "Translation:\n"
                    << pose.translation();
            LOG(INFO) << "Rotation Matrix:\n"
                    << pose.rotationMatrix();
        }

        size_t cnt_init_landmarks = 0; // 地图点计数器
        for (size_t i = 0; i < frame->features_left_.size(); ++i) {
            if (frame->features_right_[i] == nullptr)
                continue;
            std::vector<Vec3> points{
                camera_left_->pixelToCam(Vec2(frame->features_left_[i]->position_.pt.x,
                                              frame->features_left_[i]->position_.pt.y)),
                camera_right_->pixelToCam(Vec2(frame->features_right_[i]->position_.pt.x,
                                               frame->features_right_[i]->position_.pt.y)),
            };


            // for (size_t i = 0; i < points.size(); ++i)
            // {
            //     const auto &point = points[i];
            //     LOG(INFO) << "Point " << i << ": ("
            //               << point[0] << ", "
            //               << point[1] << ", "
            //               << point[2] << ")";
            // }

            Vec3 pworld = Vec3::Zero(); // 存储求解后的三维空间点

            if (triangulation(poses, points, pworld) && pworld[2] > 0) // 三角化求点在世界坐标系中的位置
            {
                LOG(INFO) << pworld;
            }
        }

        return true;
    }
}
