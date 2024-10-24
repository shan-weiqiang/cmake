AddSharedLib(
    TARGET multi
    LOGGING
    SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/multi.cpp
    PUB_DEPS nlohmann::json
    )

# Using namespace instead of target name directly, for two reasons:
# 1. cmake treat :: as only target names, if those target names are
#   not available, cmake will issue error during configuration time
#   otherwise, cmake will treat is as a library name and if the name
#   is not correct, error will happen at build time
# 2. Using namespace can organize libs more clearly
add_library(Math::Multi ALIAS multi)

# Specify VERSION and SOVERSION for a SHARED lib target will make cmake
# generate linux format soft links for *.so files. Note that this version
# is not related to project version, or package version.
set_target_properties(multi PROPERTIES
    VERSION 3.2.1
    SOVERSION 3
)

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
    # Here MUST use GNUInstallDirs variable CMAKE_INSTALL_LIBDIR to specify install
    # path, the reason is that only by this way cmake will automatically caculate
    # the correct _IMPORT_PREFIX in generated export files like *-targets.cmake
    # otherwise, absolute path will be used, which makes the exported pacakge not
    # relocatable.
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT MULTI  
)

# Install multi headers. This can also be done using PUBLIC_HEADER property
# of the target. Note that the actual install path(relative to CMAKE_INSTALL_DIR)
# should be consistent with $<INSTALL_INTERFACE>, otherwise the consumer project
# will not find header files correctly.
install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/multi
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    COMPONENT MULTI
    FILES_MATCHING PATTERN "*.h"
)
