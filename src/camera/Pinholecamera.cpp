#include "myslam/camera/Pinholecamera.h"

namespace myslam {
    Pinholecamera::Pinholecamera(double fx, double fy, double cx, double cy, double baseline,
           const SE3 &pose): fx_(fx), fy_(fy), cx_(cx), cy_(cy), baseline_(baseline), pose_(pose){};
}