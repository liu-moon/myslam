# 添加 dataset 库
add_library(dataset SHARED
    Kittidataset.cpp
)
target_link_libraries(dataset
        ${THIRD_PARTY_LIBS})