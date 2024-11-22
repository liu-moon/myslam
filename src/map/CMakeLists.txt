# 添加 map 库
add_library(map SHARED
        mappoint.cpp
        map.cpp
)
target_link_libraries(map
        ${THIRD_PARTY_LIBS})