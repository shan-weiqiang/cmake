cmake_minimum_required(VERSION 3.15)

project(app)

list(APPEND CMAKE_PREFIX_PATH "/home/swq/work/cmake/importing-exporting/my_math/build/install/lib/cmake/my_math")

find_package(my_math 3.4.1 COMPONENTS Addition)

add_executable(app app.cpp)

target_link_libraries(app PRIVATE MyMath::Addition)