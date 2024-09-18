# Add interface library
add_library(json INTERFACE)

add_library(nlohmann::json ALIAS json)

# Add json.hpp as interface includes, this will add header to INTERFACE_INCLUDE_DIRECTORIES
# of json target. Any target link to json library using INTERFACE or PUBLIC will also
# includes this header
target_include_directories(json 
    INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}> 
    INTERFACE $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    )

install(
    TARGETS json
    # Make json inside one individual export, since it might be used in different
    # components(exports)
    EXPORT JSON
    COMPONENT JSON
    )

install(
    EXPORT JSON
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}/Json
    FILE JsonConfig.cmake
    NAMESPACE nlohmann::
    COMPONENT JSON
)
include(GNUInstallDirs)

# Install header file physically
install(
    FILES json.hpp
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    COMPONENT JSON
    )