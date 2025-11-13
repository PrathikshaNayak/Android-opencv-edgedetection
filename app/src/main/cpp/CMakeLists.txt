
cmake_minimum_required(VERSION 3.10.2)

project("edgeapp")

# Add native library
add_library(native-lib SHARED native-lib.cpp)

# OpenCV setup
# If using OpenCV module added as project
# include_directories(${CMAKE_SOURCE_DIR}/../../openCVLibrary340/sdk/native/jni/include)
# target_link_libraries(native-lib ${CMAKE_SOURCE_DIR}/../../openCVLibrary340/sdk/native/jni/lib/${ANDROID_ABI}/libopencv_java4.so log)

# OR if using Maven dependency, just build your lib with log
find_library(log-lib log)

target_link_libraries(native-lib ${log-lib})
