cmake_minimum_required(VERSION 3.16)

project(bp)

enable_testing()
# Do not use CMAKE_SORUCE_DIR to support our project be used NOT as top level project,
# in which case CMAKE_SOURCE_DIR is unknown to us at now. ../cmake folder should contain
# useful modules defined for this project
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

# Include local helper functions and macros
include(BpHelpers)

# Just "use if available" recommandation
set(CMAKE_CXX_STANDARD 14)
# Force to use values set by CMAKE_CXX_STANDARD, else error at configuration time
set(CMAKE_CXX_STANDARD_REQUIRED YES)
# Flag on compiler-specific extentions, like -std=gnu++14
set(CMAKE_CXX_EXTENSIONS NO)

# Any dependent pacakges
add_subdirectory(dep)

# Current project source
add_subdirectory(src)

# Things only needed if this is top level project
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    add_subdirectory(test)
    add_subdirectory(pkg)
endif()
