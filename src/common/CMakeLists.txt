add_library(common SHARED
    viewer.cpp
)

target_link_libraries(common
        ${THIRD_PARTY_LIBS})