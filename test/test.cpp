#include <glog/logging.h>
#include "myslam/testnamespace.h"

using namespace myslam;

int main(int argc, char *argv[])
{
    // 初始化 glog
    google::InitGoogleLogging(argv[0]);

    Liu::Ptr liu = Liu::Ptr(new Liu);
    liu->printa();

    // 示例日志输出
    LOG(INFO) << "This is an info log!";
    LOG(WARNING) << "This is a warning log!";
    LOG(ERROR) << "This is an error log!";

    // 清理 glog
    google::ShutdownGoogleLogging();

    return 0;
}
