# Test for ext_modules
# say_yes is included inside nested scopes, but can be used
# here, since functions and macros have global visibility
say_yes()

add_subdirectory(multi)
add_subdirectory(divide)
add_subdirectory(caculator)

# Install MULTI_COMP_MATH export. Note that MULTI_COMP_MATH is a multi target export
# divide also use this export name, cmake will group these two targets into
# one *.cmake config file. Here we need to clarify COMPONENT(s) in cmake.
# It appears in two places: 
# 1. In the install(...) command. COMPONNET works like a label to group different
#   install sets. When installing, user can specify which components to install
#   like: cmake --install build --component MATH, in which every install content
#   that are belong to MATH will be installed. If not specified, all components
#   will be installed.
# 2. In find_package(...) command. COMPONENTS is used to locate one or more specific
#   <name>Config.cmake config file in one package. This specific config file
#   is generated for every export by cmake, thus it corresponds to an export.
#   How the components are to be found and the behavior is implemented manually
#   in the Config.cmake.in file by developer. This file will be write into the package
#   as <pkg_name>Config.cmake, where <pkg_name> is the name that should pass to
#   find_package command. Inside this file any number of `component`, aka export are
#   managed and their *.cmake file is included, conditionally based on the COMPONENTS 
#   parameter in find_package command. 

# Summary:
# 1. COMPONENT in install command is just a label to group different install content
# 2. COMPONENTS in find_package is used to specify exports inside one package
# 3. One export can contain multiple targets
# 4. Package structure is as follow: pkg --> components --> targets
#   pkg: manually managed in <pkg>Config.cmake file, which normally is generated through
#       Config.cmake.in using configure_package_config_file macro
#   components: correspond to export in cmake, <cmp>Config.cmake file will be generated
#       automatically by cmake
#   targets: will be imported inside <cmp>Config.cmake file

# MULTI_COMP_MATH is installed here since multi and divide target both belongs to it
install(EXPORT MULTI_COMP_MATH
    # ${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}/cmake/Math will produce something like
    # <install>/lib/cmake/<pkg>/<component>, this corresponds to
    # pkg --> components --> targets hierarchy
    # Note by specifying the export path, cmake will automatically generate
    # the script to locate the position of the target using relative path
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}/Math
    # This determines the name used in COMPONENTS parameter in find_package
    # for example: find_pakcage(<pkg name> <VERSION> REQUIRED COMPONENTS Math)
    FILE MathConfig.cmake
    # This determines the namespace used by consumers of targets that are inside
    # this export, for example we have divide and multi targets, they can be used
    # as Math::divide and Math::multi. Note even though this namespace is unrelated
    # with the ALIAS name and namespace inside current build tree, it normally
    # should be the same with the alias namespace. It has the benifit that the consumer
    # project can both use add_subdirectory(...) and find_pakcage(...) to use this
    # pakcage without need to change the target names.
    NAMESPACE Math::
    # This determines which install group these export files belongs to. It can
    # be specified in install command like: cmake --install build --component MATH
    # Note that export and it's containing targets can have different COMPONENT, which
    # means that targets and export can be installed individually without influencing
    # each other. Different target inside one export can also belong to different COMPONENT.
    # If target in one export and the export itself each have different COMPONENT
    # then they can be installed individually.
    COMPONENT MATH
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# This will create version config file, 
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/bpConfigVersion.cmake"
 # If not specified, VERSION in project command will be used instead
  VERSION 2.1.0
  COMPATIBILITY AnyNewerVersion
)

# This generate package level <pkg>Config.cmake file
configure_package_config_file(
    Config.cmake.in 
    bpConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
    # Those are macros that will be generated for us to manage components
    # Since we manage our components by ourself, those we do not need anymore
    NO_SET_AND_CHECK_MACRO
    NO_CHECK_REQUIRED_COMPONENTS_MACRO)

# Above command only generate bpConfig.cmake/bpConfigVersion.cmake file, but does not install it physically
# It needs to be installed explicitly
install(
    FILES 
        ${CMAKE_CURRENT_BINARY_DIR}/bpConfig.cmake 
        ${CMAKE_CURRENT_BINARY_DIR}/bpConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
    COMPONENT PKG
    )

