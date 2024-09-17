AddSharedLib(
    TARGET divide
    LOGGING
    SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/divide.cpp)

add_library(Math::Divide ALIAS divide)

include(GNUInstallDirs)
target_include_directories(divide
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include> 
    PUBLIC $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)