cmake_minimum_required(VERSION 3.15)
project(my_math)

# make cache variables for install destinations
include(GNUInstallDirs)

# include CMakePackageConfigHelpers macro
include(CMakePackageConfigHelpers)

add_subdirectory(division)
add_subdirectory(addition)

# set version
set(version 3.4.1)

# generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/my_mathConfigVersion.cmake"
  VERSION "${version}"
  COMPATIBILITY AnyNewerVersion
)

# create config file
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/my_mathConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/my_math
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

# install config files
install(FILES
          "${CMAKE_CURRENT_BINARY_DIR}/my_mathConfig.cmake"
          "${CMAKE_CURRENT_BINARY_DIR}/my_mathConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/my_math
)