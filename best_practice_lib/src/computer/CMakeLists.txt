AddExe(
    TARGET computer
    SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/computer.cpp
    PUB_DEPS Math::Caculator
)

# Like in libs, we also give alias name for executables
add_executable(Math::Computer ALIAS computer)

# Note that here we can not use Math::Computer
set_target_properties(computer PROPERTIES 
    VERSION 1.0.0
    SOVERSION 1
    # This will set RPATH for this executable to the lib dir where 
    # all the dependencies resides. This is important not that it ensures
    # the program runs correctly by finding it's dependent libs, it
    # also ensures that it finds dependencies 'correctly', with the right
    # version, by not using some other versions of lib in the system defaults.
    INSTALL_RPATH "$ORIGIN/../lib"
)

# Again we must use the original target name, not Math::Computer
install(
    TARGETS computer
    DESTINATION ${CMAKE_INSTALL_BINDIR}
    COMPONENT COMPUTER
    EXPORT EXE_EXPORT
)

install(
    EXPORT EXE_EXPORT 
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}/Computer 
    NAMESPACE Math:: 
    FILE ComputerConfig.cmake
)