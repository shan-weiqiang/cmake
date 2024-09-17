# Add interface library
add_library(json INTERFACE)

# Add json.hpp as interface includes, this will add header to INTERFACE_INCLUDE_DIRECTORIES
# of json target. Any target link to json library using INTERFACE or PUBLIC will also
# includes this header
target_include_directories(json INTERFACE 
    json.hpp)