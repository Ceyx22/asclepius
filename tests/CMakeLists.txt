
add_executable(test_hardware
        hardware/MotorTest.cpp
        hardware/ComsTest.cpp
        mocks/MockComs.h)

target_link_libraries(test_hardware
        hardware
        gtest_main
        gmock_main
        dxl_x64_cpp
        rt
)

include(GoogleTest)
gtest_discover_tests(test_hardware)