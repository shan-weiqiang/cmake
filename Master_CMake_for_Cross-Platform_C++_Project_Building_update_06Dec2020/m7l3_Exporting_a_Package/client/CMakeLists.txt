cmake_minimum_required(VERSION 3.0.0)
project(client)

include("/home/swq/work/cmake/Master_CMake_for_Cross-Platform_C++_Project_Building_update_06Dec2020/m7l3_Exporting_a_Package/build/install/lib/my_math/my_math-config.cmake")
add_executable(app app.cpp)
target_link_libraries(app PRIVATE my_math)