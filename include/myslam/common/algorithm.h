#pragma once

#include "myslam/common/common_include.h"

inline bool triangulation(const std::vector<SE3> &poses,
                          const std::vector<Vec3> points, Vec3 &pt_world)   // 原理推导 ipad
{
    MatXX A(2 * poses.size(), 4);
    LOG(INFO) << "A:" << std::endl << A;
    // VecX b(2 * poses.size());   // useless
    // b.setZero();
    for (size_t i = 0; i < poses.size(); ++i)
    {
        Mat34 m = poses[i].matrix3x4();
        LOG(INFO) << "m:" << std::endl << m;
        A.block<1, 4>(2 * i, 0) = points[i][0] * m.row(2) - m.row(0);
        LOG(INFO) << "points[i][0]:" << std::endl << points[i][0];
        LOG(INFO) << "m.row(2):" << std::endl << m.row(2);
        LOG(INFO) << "m.row(0):" << std::endl << m.row(0);
        LOG(INFO) << "A:" << std::endl << A;
        A.block<1, 4>(2 * i + 1, 0) = points[i][1] * m.row(2) - m.row(1);
        LOG(INFO) << "points[i][1]:" << std::endl << points[i][1];
        LOG(INFO) << "m.row(2):" << std::endl << m.row(2);
        LOG(INFO) << "m.row(1):" << std::endl << m.row(1);
        LOG(INFO) << "A:" << std::endl << A;
    }
    LOG(INFO) << "A:" << std::endl << A;
    auto svd = A.bdcSvd(Eigen::ComputeThinU | Eigen::ComputeThinV); // 只计算最小奇异值的特征向量
    pt_world = (svd.matrixV().col(3) / svd.matrixV()(3, 3)).head<3>();

    if (svd.singularValues()[3] / svd.singularValues()[2] < 1e-2)
    {
        // 解质量不好，放弃
        return true;
    }
    return false;
}