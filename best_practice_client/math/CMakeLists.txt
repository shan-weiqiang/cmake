cmake_minimum_required(VERSION 3.16)
project(app)

macro(list_imported_targets)
    get_property(imported_targets DIRECTORY "${CMAKE_SOURCE_DIR}" PROPERTY IMPORTED_TARGETS)
    message(STATUS "Imported Targets:")
    foreach(target IN LISTS imported_targets)
        message(STATUS " - ${target}")
    endforeach()
endmacro()

add_executable(app app.cpp)
list(PREPEND CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/../../best_practice_lib/build/install/lib/cmake)

list_imported_targets()
# Package name, component name are related to the config file name
# This will import all targets inside Math component: Math::multi, Math::divide
find_package(bp REQUIRED COMPONENTS Math) 
list_imported_targets()

# Target name namespace are related to the NAMESPACE in install(EXPORT...)
# and actual target name
target_link_libraries(app PRIVATE Math::divide)