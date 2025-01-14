add_executable(asclepius main.cpp)

target_link_libraries(asclepius PUBLIC controller util hardware dxl_x64_cpp rt)