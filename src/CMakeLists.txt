add_library(myslam SHARED
    testnamespace.cpp
)

add_subdirectory(frontend)
add_subdirectory(common)
add_subdirectory(dataset)
add_subdirectory(camera)
add_subdirectory(map)

target_link_libraries(myslam
        ${THIRD_PARTY_LIBS})