# Add the controller library
add_library(controller
        EndEffector.cpp
        EndEffector.h
        TrajectoryController.cpp
        TrajectoryController.h
)

target_link_libraries(controller PUBLIC util hardware)

target_include_directories(controller PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
