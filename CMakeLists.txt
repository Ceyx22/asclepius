cmake_minimum_required(VERSION 3.30)
project(asclepius)
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(DEBUG_SUFFIX "d")
endif ()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -O3 -DLINUX -D_GNU_SOURCE -Wall -g -m64")

set(QT_VERSION 6)
set(CMAKE_PREFIX_PATH "/home/ceyx/Qt/6.8.1/gcc_64/lib/cmake")
#set(CMAKE_MODULE_PATH "/home/ceyx/Qt/6.8.1/gcc_64/lib/cmake")
#find_package(Qt6Widgets REQUIRED)
#find_package(Qt6Charts REQUIRED)
#find_package(Qt6Gui REQUIRED)
#find_package(Qt6Core REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Charts)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set_property(SOURCE main.cpp PROPERTY SKIP_AUTOMOC ON)
set(SOURCES
        main.cpp
        hardware/Motor.cpp
        hardware/Motor.h
        hardware/Coms.cpp
        hardware/Coms.h
        util/LoggerManager.cpp
        util/LoggerManager.h
        robot/EndEffector.cpp
        robot/EndEffector.h
        util/Scheduler.cpp
        util/Scheduler.h
        hardware/Constants.h
)

set(LIBRARIES dxl_x64_cpp rt)

include_directories(${CMAKE_SOURCE_DIR}/hardware)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Charts)


