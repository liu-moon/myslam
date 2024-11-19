cmake_minimum_required(VERSION 3.20.0)

project(myslam CXX)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Glog
find_package(Glog REQUIRED)
include_directories(${GLOG_INCLUDE_DIRS})

set(THIRD_PARTY_LIBS
        glog::glog
        ${OpenCV_LIBS})

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(app)