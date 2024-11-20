# 添加 frontend 库
add_library(frontend SHARED
    ORBfrontend.cpp
        OpticalFlowfrontend.cpp
)
target_link_libraries(frontend
        ${THIRD_PARTY_LIBS})