cmake_minimum_required(VERSION 3.21)
project(app)

macro(list_imported_targets)
    get_property(imported_targets DIRECTORY "${CMAKE_SOURCE_DIR}" PROPERTY IMPORTED_TARGETS)
    message(STATUS "Imported Targets:")
    foreach(target IN LISTS imported_targets)
        message(STATUS " - ${target}")
    endforeach()
endmacro()

add_executable(app app.cpp)

if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
    list(PREPEND CMAKE_PREFIX_PATH 
        ${CMAKE_SOURCE_DIR}/../../best_practice_lib/build/install/lib/cmake
        # external pkg
        ${CMAKE_SOURCE_DIR}/../../best_practice_lib/ext/x86/lib
        )
else()
    list(PREPEND CMAKE_PREFIX_PATH 
        ${CMAKE_SOURCE_DIR}/../../best_practice_lib/build/install/lib/cmake
        # external pkg
        ${CMAKE_SOURCE_DIR}/../../best_practice_lib/ext/aarch64/lib
        )
endif()

list_imported_targets()
# Package name, component name are related to the config file name
# This will import component Caculator and it's dependent components
# Also the version number 2.1.0 will also be check to decides whether
# the actual version meets the version specified here
find_package(bp 2.1.0 EXACT COMPONENTS Caculator)
list_imported_targets()

# Target name namespace are related to the NAMESPACE in install(EXPORT...)
# and actual target name
# Note that end user who uses Caculator component does not need to explicitly
# link to libraries that are dependented by Caculator. Math::divide and Math::multi
# are PUBLIC linked by Math::Caculator, cmake will automatically link to Math::divide
# and Math::multi. This also works for header includes
target_link_libraries(app PRIVATE Math::Caculator)