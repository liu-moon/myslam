# 添加可执行文件
add_executable(test test.cpp)
add_executable(gftt test_gftt.cpp)
add_executable(main main.cpp)


target_link_libraries(test
        myslam
        ${THIRD_PARTY_LIBS})


target_link_libraries(gftt 
        myslam
        ${THIRD_PARTY_LIBS})        

target_link_libraries(main 
        myslam
        frontend
        common
        dataset
        ${THIRD_PARTY_LIBS})     