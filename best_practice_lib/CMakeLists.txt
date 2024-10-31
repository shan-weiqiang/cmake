cmake_minimum_required(VERSION 3.21)

# Call project in the top level CMakeLists.txt just once(best practice)
project(bp
    # This version will be used by write_basic_package_version_file commands if
    # it is called without VERSION specified
    VERSION 1.1.0
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/shan-weiqiang/cmake/tree/main/best_practice_lib
    DESCRIPTION "A project to demonstrate the best practice for using CMake"
)

enable_testing()
# Do not use CMAKE_SORUCE_DIR to support our project be used NOT as top level project,
# in which case CMAKE_SOURCE_DIR is unknown to us at now. ../cmake folder should contain
# useful modules defined for this project
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

# External library search path
if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
    list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_LIST_DIR}/ext/x86/lib/foonathan_memory/cmake)
else()
    list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_LIST_DIR}/ext/aarch64/lib/foonathan_memory/cmake)
endif()

# Include local helper functions and macros
include(BpHelpers)

include(GNUInstallDirs)

# Just "use if available" recommandation
set(CMAKE_CXX_STANDARD 14)
# Force to use values set by CMAKE_CXX_STANDARD, else error at configuration time
set(CMAKE_CXX_STANDARD_REQUIRED YES)
# Flag on compiler-specific extentions, like -std=gnu++14
set(CMAKE_CXX_EXTENSIONS NO)

# Make cmake modify RPATH for *.so to contain relative locations when targets are installed
set(CMAKE_INSTALL_RPATH $ORIGIN)

# Any dependent pacakges
add_subdirectory(dep)

# Current project source
add_subdirectory(src)

# Things only needed if this is top level project
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    add_subdirectory(test)
    add_subdirectory(pkg)
endif()
