cmake_minimum_required(VERSION 3.22.1)

project("assessment_native")

add_library(
        assessment_native
        SHARED
        native-lib.cpp
)

find_library(
        log-lib
        log
)

target_link_libraries(
        assessment_native
        ${log-lib}
)
