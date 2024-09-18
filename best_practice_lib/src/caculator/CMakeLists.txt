AddSharedLib(
    TARGET Caculator 
    SOURCES src/caculator.cpp 
    PUB_DEPS Math::Divide Math::Multi
)

add_library(Math::Caculator ALIAS Caculator)

set_target_properties(Caculator PROPERTIES
    VERSION 3.2.1
    SOVERSION 3
)

include(GNUInstallDirs)
target_include_directories(Caculator 
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    PUBLIC $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

install(
    TARGETS Caculator
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT CACULATOR
    # This is a single target export that only contains one target
    EXPORT SINGLE_COMP_EXPORT
)

install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/caculator
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    COMPONENT CACULATOR
    FILES_MATCHING PATTERN "*.h"
    )

install(EXPORT SINGLE_COMP_EXPORT
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
    NAMESPACE Math::
    FILE CaculatorConfig.cmake
    )