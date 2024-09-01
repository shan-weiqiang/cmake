add_library(Division STATIC src/division.cpp)
add_library(my_math::Division ALIAS Division)
target_include_directories(Division
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/a/b/c>
        )

install(TARGETS Division
        EXPORT DivisionExport
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES include/division.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/a/b/c)

install(EXPORT DivisionExport
        FILE my_mathDivision-config.cmake
        NAMESPACE MyMath::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/my_math)        