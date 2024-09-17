FetchContent_GetProperties(ext_modules)
if(NOT ext_modules_POPULATED)
    FetchContent_Populate(ext_modules)
    list(APPEND CMAKE_MODULE_PATH ${ext_modules_SOURCE_DIR}/cmake)
endif()

# Include here, since CMAKE_MODULE_PATH modified above only works inside current
# scope. However, the functions and macros defined inside SayYes are valid in 
# all parent and above scopes, since functions and macros in cmake have global
# visibility!
include(SayYes)