#include "myslam/camera/Pinholecamera.h"

namespace myslam {
    Pinholecamera::Pinholecamera(double fx, double fy, double cx, double cy, double baseline,
                                 const SE3 &pose): fx_(fx), fy_(fy), cx_(cx), cy_(cy), baseline_(baseline),
                                                   pose_(pose) {
    };

    /**
     * @brief 通过针孔相机模型计算像素点在空间中的位置
     * @param p_p 像素坐标
     * @param depth 深度(默认为1)
     * @return 像素点在空间中的三维坐标
     */
    Vec3 Pinholecamera::pixelToCam(const Vec2 &p_p, double depth) {
        /*
            |u|            |fx    cx|   |X|
            |v| = Z^{-1} * |   fy cy| * |Y|
            |1|            |       1|   |Z|
            -------------------------------
            X = [Z(u - cx)] / fx
            Y = [Z(u - cy)] / fy
            Z = Z
        */
        return Vec3(
            (p_p(0, 0) - cx_) * depth / fx_,
            (p_p(1, 0) - cy_) * depth / fy_,
            depth
        );
    }
}
