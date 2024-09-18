# Find external pakcages
find_package(foonathan_memory REQUIRED)

AddSharedLib(
    TARGET divide
    LOGGING
    SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/divide.cpp
    PUB_DEPS foonathan_memory
    )

add_library(Math::Divide ALIAS divide)

set_target_properties(divide PROPERTIES
    VERSION 3.2.1
    SOVERSION 3
)

include(GNUInstallDirs)
target_include_directories(divide
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include> 
    PUBLIC $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

install(TARGETS divide
    EXPORT   MULTI_COMP_MATH
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT DIVIDE  
)

install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/divide
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    COMPONENT DIVIDE
    FILES_MATCHING PATTERN "*.h"
)