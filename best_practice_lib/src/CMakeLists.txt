# Test for ext_modules
# say_yes is included inside nested scopes, but can be used
# here, since functions and macros have global visibility
say_yes()

add_subdirectory(multi)
add_subdirectory(divide)
add_subdirectory(caculator)

