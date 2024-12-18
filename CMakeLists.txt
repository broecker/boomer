cmake_minimum_required(VERSION 3.5.0)
project(boomer
    VERSION 0.0.0
    DESCRIPTION "Boomershooter project."
    LANGUAGES CXX)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

include_directories(.)
add_executable(boomer "main.cpp")
target_link_libraries(boomer ${SDL2_LIBRARIES})