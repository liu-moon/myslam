add_library(camera SHARED
    Pinholecamera.cpp
)

target_link_libraries(camera
        ${THIRD_PARTY_LIBS})