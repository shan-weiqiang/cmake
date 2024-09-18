AddSharedLib(
    TARGET multi
    LOGGING
    SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/multi.cpp)

# Using namespace instead of target name directly, for two reasons:
# 1. cmake treat :: as only target names, if those target names are
#   not available, cmake will issue error during configuration time
#   otherwise, cmake will treat is as a library name and if the name
#   is not correct, error will happen at build time
# 2. Using namespace can organize libs more clearly
add_library(Math::Multi ALIAS multi)

include(GNUInstallDirs)

# Specify include folders for build time and export time
# BUILD_INTERFACE will be used as build time include search path
# and targets that directly depend on this lib in current build tree
# INSTALL_INTERFACE will be used as INTERFACE_* property for exported
# target
target_include_directories(multi
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include> 
    PUBLIC $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# Install multi target. Note that MULTI_COMP_MATH is a multi component export
# divide also use this export name, cmake will group these two components into
# one *.cmake config file. 
install(TARGETS multi
    EXPORT   MULTI_COMP_MATH
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT MULTI  
)

# Install multi headers. This can also be done using PUBLIC_HEADER property
# of the target
install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/multi
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    COMPONENT MULTI
    FILES_MATCHING PATTERN "*.h"
)
