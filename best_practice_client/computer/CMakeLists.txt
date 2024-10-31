cmake_minimum_required(VERSION 3.21)
project(app)

macro(list_imported_targets)
    get_property(imported_targets DIRECTORY "${CMAKE_SOURCE_DIR}" PROPERTY IMPORTED_TARGETS)
    message(STATUS "Imported Targets:")
    foreach(target IN LISTS imported_targets)
        message(STATUS " - ${target}")
    endforeach()
endmacro()


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
find_package(bp 2.1.0 EXACT COMPONENTS Computer)
list_imported_targets()

add_custom_command(
    OUTPUT result
    COMMAND Math::computer
    COMMENT "Executing Math::computer..."
)

# Make a target so that our custom command will be run
add_custom_target(run_custom_commands ALL DEPENDS result)
