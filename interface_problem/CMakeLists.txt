cmake_minimum_required(VERSION 3.21)

project(p)

add_library(B SHARED  B.cpp)

add_library(A SHARED  A.cpp)

add_executable(app app.cpp)

# Here INTERFACE is used since A's cpp and implementation does not depend on B
# A is only a interface library(in C++' sense, not in cmake'sense, since it has
# binaries and have code with it). A's job is to provide user might be a unified
# calling interface and at the same time, with B as it's INTERFACE dependency
# tells user that what actual objects he can create and pass to it's interface APIs.

# If we change INTERFACE to PUBLIC, it will not change the final result, libA still
# will not depend on libB(check with ldd command). But if we comment out this line
# there will be link errors, since app.cpp depends on A and B, since it only include
# A's headers, it's weird to link to B. Instead the lib dependency is implied here.
target_link_libraries(A INTERFACE B)

target_link_libraries(app PRIVATE A)
