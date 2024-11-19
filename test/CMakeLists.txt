# 添加可执行文件
add_executable(test test.cpp)


target_link_libraries(test 
        # myslam
        ${THIRD_PARTY_LIBS})