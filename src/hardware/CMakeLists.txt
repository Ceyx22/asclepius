add_library(hardware
        Coms.h Coms.cpp Motor.h Motor.cpp
        ComsBase.h
)

target_link_libraries(hardware PUBLIC util)

target_include_directories(hardware PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
