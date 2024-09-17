AddSharedLib(
    TARGET Caculator 
    SOURCES src/caculator.cpp 
    PUB_DEPS Math::Divide Math::Multi
)

add_library(Math::Caculator ALIAS Caculator)

include(GNUInstallDirs)
target_include_directories(Caculator 
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    PUBLIC $<INSTALL_INTERFACE: ${CMAKE_INSTALL_INCLUDEDIR})