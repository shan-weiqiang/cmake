add_library(my_math
src/addition.cpp
src/division.cpp)

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
$<INSTALL_INTERFACE:include>
# 这个是当前build或者，当前构建系统中被使用时target的INTERFACE_INCLUDE_DIRECTORIES
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/my_math/addition.h ${CMAKE_CURRENT_SOURCE_DIR}/include/my_math/division.h  DESTINATION ${CMAKE_INSTALL_PREFIX}/include/my_math)

install(TARGETS my_math EXPORT my_export DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/my_math)

install(EXPORT my_export FILE my_math-config.cmake DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/my_math)
