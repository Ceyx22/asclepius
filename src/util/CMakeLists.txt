add_library(util LoggerManager.cpp LoggerManager.h MathUtil.cpp MathUtil.h
        Result.h)

target_include_directories(util PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
