
include(FetchContent)

FetchContent_Declare(gtest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG b514bdc)

add_subdirectory(gtest)