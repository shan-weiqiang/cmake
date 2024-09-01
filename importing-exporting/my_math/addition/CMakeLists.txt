add_library(Addition STATIC src/addition.cpp)
add_library(my_math::Addition ALIAS Addition)
target_include_directories(Addition
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/a/b/c>
        )

install(TARGETS Addition
        EXPORT AdditionExport
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES include/addition.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/a/b/c)

install(EXPORT AdditionExport
        FILE my_mathAddition-config.cmake
        NAMESPACE MyMath::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/my_math)        