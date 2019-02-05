cmake_minimum_required(VERSION 3.02)
project(autojson)

option(AJ_WITH_SAMPLE "Build sample application" off)

add_library(autojson INTERFACE)
target_include_directories(autojson INTERFACE include)

if (${AJ_WITH_SAMPLE})
    add_executable(sample sample/main.cpp)
    target_link_libraries(sample autojson)
endif()