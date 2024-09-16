
include(FetchContent)

# Introduce google test
FetchContent_Declare(gtest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG b514bdc)

# Introduce useful external cmake modules
FetchContent_Declare(ext_modules
    GIT_REPOSITORY https://github.com/shan-weiqiang/cmake.git
    GIT_TAG main)

add_subdirectory(gtest)
add_subdirectory(ext_modules)