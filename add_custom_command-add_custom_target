# Original article: https://gist.github.com/baiwfg2/39881ba703e9c74e95366ed422641609

# References:
# https://cmake.org/cmake/help/latest/command/add_custom_target.html
# https://samthursfield.wordpress.com/2015/11/21/cmake-dependencies-between-targets-and-files-and-custom-commands/
# https://gist.github.com/socantre/7ee63133a0a3a08f3990
# https://stackoverflow.com/questions/24163778/how-to-add-custom-target-that-depends-on-make-install
# https://stackoverflow.com/questions/30719275/add-custom-command-is-not-generating-a-target
# https://stackoverflow.com/questions/26024235/how-to-call-a-cmake-function-from-add-custom-target-command
# https://blog.csdn.net/gubenpeiyuan/article/details/51096777

cmake_minimum_required(VERSION 3.10)
project(foo)

set(TEST_FILE "${CMAKE_CURRENT_LIST_DIR}/app.cpp.in")

# add_custom_command does not create a new target. You have to define targets explicitly
# by add_executable, add_library or add_custom_target in order to make them visible to make
add_custom_command(
    OUTPUT "${CMAKE_CURRENT_LIST_DIR}/app.cpp"
    COMMAND cp ${TEST_FILE} "${CMAKE_CURRENT_LIST_DIR}/app.cpp"
    # Display the given message before the commands are executed at build time
    COMMENT "Creating ${TEST_FILE}"
    # If ${TEST_FILE} changes, re-run this command at build time
    DEPENDS ${TEST_FILE}
)

# target zoo is always built(always considered out of date)
add_custom_target(zoo ALL
    COMMAND echo "This is ALL target 'zoo', and it depends on ${TEST_FILE}"
    # If the file exists, then commands related to that file won't be executed(except that
    # commands dependencies are changed, see above)

    # DONOT let other target depends on the same OUTPUT as current target,
    #   or it may be bad when doing parallel make
    DEPENDS "${CMAKE_CURRENT_LIST_DIR}/app.cpp"

    # to make quotes printable,for example
    VERBATIM
)

# target bar is only build when `make bar` is issued
add_custom_target(bar
    COMMAND ${CMAKE_COMMAND} -E echo bar:hello

    COMMENT "testing add_custom_target 'bar'..."
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}

    #DEPENDS zoo
)
# It seems to be same as `DEPENDS zoo` above
add_dependencies(bar zoo)

# This is the second signature of add_custom_command, which adds a custom command
# to a target such as a library or executable. This is useful for performing an 
# operation before or after building the target. The command becomes part of the 
# target and will only execute when the target itself is built. If the target is 
# already built, the command will not execute
add_custom_command(TARGET bar
    PRE_BUILD
    COMMAND echo -e "\texecuting a PRE_BUILD command"
    COMMENT "This command will be executed before building bar"
    VERBATIM # to support \t for example
)

add_custom_command(TARGET bar
    # Run after sources have been compiled but before linking the binary or 
    # running the librarian or archiver tool of a static library. 
    # This is not defined for targets created by the add_custom_target() command
    PRE_LINK
    COMMAND echo -e "\texecuting a PRE_LINK command"
    COMMENT "This command will be executed after building bar"
    VERBATIM
)

add_custom_command(TARGET bar
    # Run after all other rules within the target have been executed
    POST_BUILD
    COMMAND echo -e "\texecuting a POST_BUILD command"
    COMMENT "This command will be executed after building bar"
    VERBATIM
)
