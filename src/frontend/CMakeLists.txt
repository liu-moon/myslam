# 添加 frontend 库
add_library(frontend SHARED
    ORBfrontend.cpp
        OpticalFlowFrontend.cpp
)

# add_library(myslam SHARED
#     testnamespace.cpp
# )

# # 包含头文件目录
# target_include_directories(frontend PUBLIC
#     ${PROJECT_SOURCE_DIR}/include  # 主项目的 include 目录
# )

# # 链接第三方库
# target_link_libraries(frontend PUBLIC
#     ${OpenCV_LIBS}  # OpenCV 库
#     glog::glog      # Glog 库
# )

# # 添加到顶层可见
# set(FRONTEND_LIB frontend PARENT_SCOPE)
