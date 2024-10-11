
FetchContent_GetProperties(gtest)

# Check if is it already be downloaded, if not downlowd it and add_subdir
if(NOT gtest_POPULATED)
    # This will create "<build>/_deps/gtest_subbuild" directory, in which a new
    # project called "gtest-populate" will be created automatically
    FetchContent_Populate(gtest)
    # gtest_SOURCE_DIR wil be assigned to "<build>/_deps/gtest_src", in which the
    # downlaoded content will be stored
    # gtest_BINARY_DIR will be assigned to "<build>/_deps/gtest_build", where acutual
    # building will happen
    add_subdirectory(${gtest_SOURCE_DIR} ${gtest_BINARY_DIR})
endif()
