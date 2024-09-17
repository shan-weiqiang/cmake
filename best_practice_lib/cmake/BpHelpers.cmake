# Demonstrate the usage of function and keywords arguments
function(AddExe)
    # cmake_parse_arguments must have those parameters, if one is not required
    # empty string should be used as placeholder
    set(prefix ARG)
    set(noValue LOGGING)
    set(oneValue TARGET)
    # Every type can be a list of keywords
    set(multiValues SOURCES PUB_DEPS)

    # Note the double quotes are required to add ';' for it to be list other than
    # individual parameter
    cmake_parse_arguments(
        ${prefix}
        "${noValue}"
        "${oneValue}"
        "${multiValues}"
        ${ARGN}
        )
    list(LENGTH ARG_SOURCES source_len)
    if(source_len LESS 1)
        message(FATAL_ERROR "target must have source files!")
    endif()
    if("${ARG_TARGET}" STREQUAL "")
        message(FATAL_ERROR "target must have names!")
    endif()
    if(ARG_LOGGING)
        message(STATUS "creating target: ${ARG_TARGET}")
    endif()
    add_executable(${ARG_TARGET} "${ARG_SOURCES}")
    target_link_libraries(${ARG_TARGET} PUBLIC ${ARG_PUB_DEPS})
endfunction(AddExe)

# Add Libs
function(AddSharedLib)
    set(prefix ARG)
    set(noValue LOGGING)
    set(oneValue TARGET)
    set(multiValues SOURCES PUB_DEPS)
    cmake_parse_arguments(
        ${prefix}
        "${noValue}"
        "${oneValue}"
        "${multiValues}"
        ${ARGN}
        )
    list(LENGTH ARG_SOURCES source_len)
    if(source_len LESS 1)
        message(FATAL_ERROR "target must have source files!")
    endif()
    if("${ARG_TARGET}" STREQUAL "")
        message(FATAL_ERROR "target must have names!")
    endif()
    if(ARG_LOGGING)
        message(STATUS "creating target: ${ARG_TARGET}")
    endif()
    add_library(${ARG_TARGET} SHARED "${ARG_SOURCES}")
    target_link_libraries(${ARG_TARGET} PUBLIC ${ARG_PUB_DEPS})
endfunction(AddSharedLib)
