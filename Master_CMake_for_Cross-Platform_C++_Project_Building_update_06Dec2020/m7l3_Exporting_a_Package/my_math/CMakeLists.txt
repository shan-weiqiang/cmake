add_library(my_math
src/addition.cpp
src/division.cpp)

include(GNUInstallDirs)

# https://cmake.org/cmake/help/latest/guide/importing-exporting/index.html

# Include directories usage requirements commonly differ between the build-tree and the install-tree. 
# The BUILD_INTERFACE and INSTALL_INTERFACE generator expressions can be used to describe separate usage 
# requirements based on the usage location. Relative paths are allowed within the INSTALL_INTERFACE 
# expression and are interpreted relative to the installation prefix. For example:
# target_include_directories(mylib PUBLIC  
#     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/mylib>  
#     $<INSTALL_INTERFACE:include/mylib>  # <prefix>/include/mylib
# )

# target_include_directories(my_math PUBLIC include)
target_include_directories( my_math PUBLIC
# 这个是用在export后，当前target被作为IMPORTED_TARGET使用时的INTERFACE_INCLUDE_DIRECTORIES路径，前缀是install的位置路径
# 这个必须使用generator expression，因为只有在configuration全部结束后（CMakeLists.txt文件全部被处理完）后，cmake才知道
# 有没有使用export，如果使用了export，则解析成相<install path>/include，否则解析成空字符串

# 这里的INSTALL_INTERFACE定义了export target的INTERFACE_INCLUDE_DIRECTORIES的值，它是相对实际安装位置的路径
# 需要与头文件在install命令中实际安装位置对应
$<INSTALL_INTERFACE:include/a/b/c>
# 这个是当前build或者，当前构建系统中被使用时target的INTERFACE_INCLUDE_DIRECTORIES
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

install(
    FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/my_math/addition.h ${CMAKE_CURRENT_SOURCE_DIR}/include/my_math/division.h  
    # 注意: 这里也可以指定,cmake也会自动安装，但是在生成的EXPORT .cmake文件中INTERFACE_INCLUDE_DIRECTORIES是由上面的$<INSTALL_INTERFACE:include/a/b/c>
    # 确定的，也就是说target_include_directories中的$<INSTALL_INTERFACE:include/a/b/c>定义了export的target的INTERFACE_INCLUDE_DIRECTORIES属性值
    # 而真正的文件安装位置是在这里指定的，所以这两个地方要保持一致，否则的话export的target在使用时就找不到对应的头文件路径
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/a/b/c/my_math)

install(
    TARGETS my_math
    # 这里库的安装路径可以任意指定，cmake会自动在生成的EXPORT .cmake脚本中考虑库的路径 
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/my_math/a/b/c
    EXPORT my_export)

install(
    EXPORT my_export 
    FILE my_math-config.cmake
    NAMESPACE MyMath::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/my_math/cmake)
    # 避免使用CMAKE_INSTALL_PREFIX，生成的my_math-config.cmake中的_IMPORT_PREFIX是绝对路径，not relocatable
    # 使用GNUInstallDirs中的CMAKE_INSTALL_LIBDIR，cmake会在生成物中计算相对路径，让生成的install内容relocatable
    # DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/my_math)

##########################################################################################################
# 注意：
# 以上内容可以实现在下游用户那里使用include(..)的方式使用export的target，例如：
# include("/home/swq/work/cmake/Master_CMake_for_Cross-Platform_C++_Project_Building_update_06Dec2020/m7l3_Exporting_a_Package/build/install/lib/my_math/cmake/my_math-config.cmake")
# 以上的一个export的target是下面find_package以及后续COMPONENT的基本操作target

# 但是不能支持使用find_package(..)，以下的内容增加对find_package(..)的使用支持
# 增加find_package的支持后，原来的include(..)的使用方式仍然不变，依然可以使用
##########################################################################################################

include(CMakePackageConfigHelpers)

# set version
set(version 3.4.1)

set_property(TARGET my_math PROPERTY VERSION ${version})
set_property(TARGET my_math PROPERTY SOVERSION 3)
set_property(TARGET my_math PROPERTY
  INTERFACE_my_math_MAJOR_VERSION 3)
set_property(TARGET my_math APPEND PROPERTY
  COMPATIBLE_INTERFACE_STRING my_math_MAJOR_VERSION
)

# generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/my_mathConfigVersion.cmake"
  VERSION "${version}"
  COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/my_mathConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/my_math/cmake)

install(FILES 
    "${CMAKE_CURRENT_BINARY_DIR}/my_mathConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/my_mathConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/my_math/cmake)


