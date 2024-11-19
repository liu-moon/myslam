#include <glog/logging.h>

int main(int argc, char* argv[]) {
    // 初始化 glog
    google::InitGoogleLogging(argv[0]);

    // 示例日志输出
    LOG(INFO) << "This is an info log!";
    LOG(WARNING) << "This is a warning log!";
    LOG(ERROR) << "This is an error log!";

    // 清理 glog
    google::ShutdownGoogleLogging();
    return 0;
}
