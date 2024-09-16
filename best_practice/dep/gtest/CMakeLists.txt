
FetchContent_GetProperties(gtest)

# Check if is it already be downloaded, if not downlowd it and add_subdir
if(NOT gtest_POPULATED)
    FetchContent_Populate(gtest)
    add_subdirectory(${gtest_SOURCE_DIR} ${gtest_BINARY_DIR})
endif()