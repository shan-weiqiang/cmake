cmake_minimum_required(VERSION 3.0.0)
project(client)

# 如下的使用方式依然支持
# include("/home/swq/work/cmake/Master_CMake_for_Cross-Platform_C++_Project_Building_update_06Dec2020/m7l3_Exporting_a_Package/build/install/lib/my_math/cmake/my_math-config.cmake")

# find_package的使用方式
list(APPEND CMAKE_PREFIX_PATH "/home/swq/work/cmake/Master_CMake_for_Cross-Platform_C++_Project_Building_update_06Dec2020/m7l3_Exporting_a_Package/build/install/lib/my_math/cmake")
find_package(my_math 3.4.1 REQUIRED)


add_executable(app app.cpp)
target_link_libraries(app PRIVATE MyMath::my_math)