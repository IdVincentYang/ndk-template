cmake_minimum_required(VERSION 3.4.1)

add_subdirectory(shared)

if(DEFINED BUILD_APP_INPUT_QUEUE)
    add_subdirectory(app-input-queue)
endif()

if(DEFINED BUILD_NATIVE_ACTIVITY)
    add_subdirectory(app-native-activity)
endif()