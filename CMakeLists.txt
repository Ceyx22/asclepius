cmake_minimum_required(VERSION 3.30)
project(asclepius)
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(DEBUG_SUFFIX "d")
endif ()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set_property(SOURCE main.cpp PROPERTY SKIP_AUTOMOC ON)

set(SOURCES
        main.cpp
        hardware/Motor.cpp
        hardware/Motor.h
        hardware/Coms.cpp
        hardware/Coms.h
        util/LoggerManager.cpp
        util/LoggerManager.h
        controller/EndEffector.cpp
        controller/EndEffector.h
        util/Scheduler.cpp
        util/Scheduler.h
        hardware/Constants.h
        util/MathUtil.cpp
        util/MathUtil.h
        controller/Trajectory.cpp
        controller/Trajectory.h
)

set(LIBRARIES dxl_x64_cpp rt)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})


