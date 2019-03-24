
set(_LIB_NAME native-lib)
add_library(${_LIB_NAME}
        SHARED
        src/main/cpp/native-lib.cpp
        )

find_library(_LIB_LOG log)
find_library(_LIB_ANDROID android)

target_link_libraries(${_LIB_NAME}
        ${_LIB_LOG}
        ${_LIB_ANDROID}
        nt-shared-static
        )