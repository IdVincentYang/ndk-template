
set(_LIB_NAME nt-shared-static)

add_library(${_LIB_NAME}
        STATIC
        "")

target_sources(${_LIB_NAME}
        PRIVATE
        ./src/native-activity.cxx
        ./src/pal-log.cxx
        )

target_include_directories(${_LIB_NAME}
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        )