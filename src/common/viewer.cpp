#include "myslam/common/viewer.h"
#include <unistd.h> // usleep 所在的库

namespace myslam {
    void Viewer::DisplayKeypoints(const Frame::Ptr frame, bool show_left) {
        cv::Mat output_image;

        if (show_left) {
            // 处理左图
            cv::cvtColor(frame->left_img_, output_image, cv::COLOR_BGR2RGB);
            for (size_t i = 0; i < frame->features_left_.size(); i++) {
                auto feat = frame->features_left_[i];
                cv::circle(output_image, feat->position_.pt, 2, cv::Scalar(0, 255, 0), 2);
            }
        } else {
            // 处理右图
            cv::cvtColor(frame->right_img_, output_image, cv::COLOR_BGR2RGB);
            for (size_t i = 0; i < frame->features_right_.size(); i++) {
                auto feat = frame->features_right_[i];
                if (feat) {
                    // 确保特征点非空
                    cv::circle(output_image, feat->position_.pt, 2, cv::Scalar(255, 0, 0), 2);
                }
            }
        }

        // 显示图像
        cv::imshow(show_left ? "Left Image" : "Right Image", output_image);
        cv::waitKey(0); // 等待按键关闭窗口
    }

    void Viewer::DrawFeatureMatches(const cv::Mat &img_left, const cv::Mat &img_right,
                                    const std::vector<cv::Point2f> &kps_left, const std::vector<cv::Point2f> &kps_right,
                                    const std::vector<uchar> &status) {
        // 创建一张新图，用于拼接左右图像
        cv::Mat img_matches;
        cv::hconcat(img_left, img_right, img_matches); // 将左右图像水平拼接

        // 遍历特征点并绘制连线和点
        for (size_t i = 0; i < kps_left.size(); ++i) {
            if (status[i]) {
                // 只绘制匹配成功的特征点
                // 左图中的特征点
                cv::Point2f pt_left = kps_left[i];
                // 右图中的特征点，右图的点需要偏移到拼接后的图像右半部分
                cv::Point2f pt_right = kps_right[i] + cv::Point2f((float) img_left.cols, 0);

                // 随机生成颜色
                cv::Scalar color = cv::Scalar(rand() % 255, rand() % 255, rand() % 255);

                // 绘制连线
                cv::line(img_matches, pt_left, pt_right, color, 1, cv::LINE_AA);
                // 绘制特征点
                cv::circle(img_matches, pt_left, 5, color, -1);
                cv::circle(img_matches, pt_right, 5, color, -1);
            }
        }

        // 显示匹配图
        cv::imshow("Feature Matches", img_matches);
        cv::waitKey(0); // 等待用户按键
    }

    void Viewer::DrawMapPoints() {
        const float red[3] = {1.0, 0, 0}; // 红色
        // for (auto &kf : active_keyframes_) // 遍历所有活跃关键帧
        // {
        //     DrawFrame(kf.second, red); // 画视锥体
        // }

        glPointSize(2); // 设置点的大小 2 个像素
        glBegin(GL_POINTS); // 通知 OpenGL 开始绘制点
        for (auto &landmark: active_landmarks_) // 遍历当前活跃地图点
        {
            auto pos = landmark.second->Pos(); // 从 landmark 中提取出地图点的位置
            glColor3f(red[0], red[1], red[2]); // 设置当前绘图的颜色
            glVertex3d(pos[0], pos[1], pos[2]); // 绘制一个点
        }
        glEnd(); // 结束绘制点
    }

    void Viewer::ThreadLoop() {
        // 创建一个名为 "Map Viewer" 的窗口
        pangolin::CreateWindowAndBind("Map Viewer", 1024, 768);

        // 启用深度测试
        glEnable(GL_DEPTH_TEST);

        // 设置摄像机参数
        pangolin::OpenGlRenderState s_cam(
            pangolin::ProjectionMatrix(1024, 768, 500, 500, 512, 389, 0.1, 1000), // 投影矩阵
            pangolin::ModelViewLookAt(0, -10, -10, 0, 0, 0, pangolin::AxisY) // 视图矩阵
        );

        // 创建显示面板并绑定摄像机
        pangolin::View &d_cam = pangolin::CreateDisplay()
                .SetBounds(0.0, 1.0, pangolin::Attach::Pix(175), 1.0, -1024.0f / 768.0f) // 设置视口边界
                .SetHandler(new pangolin::Handler3D(s_cam)); // 绑定 3D 交互控制

        while (!pangolin::ShouldQuit()) {
            // 主循环，直到窗口关闭
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清空颜色和深度缓冲

            d_cam.Activate(s_cam); // 激活摄像机

            DrawMapPoints(); // 绘制地图点

            pangolin::FinishFrame(); // 完成当前帧的绘制
        }
    }

    void Viewer::UpdateMap() {
        active_landmarks_ = map_->GetActiveMapPoints(); // 获取活跃地图点
    }
}
