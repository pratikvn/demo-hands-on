cmake_minimum_required(VERSION 3.16)

project(
    DemoHandsOn
    LANGUAGES CXX
)

option(BUILD_DEMOS "Build demos" ON)
option(BUILD_HANDS_ON "Build hands-on" ON)


if(BUILD_DEMOS)
  add_subdirectory(demo)
endif()

if(BUILD_HANDS_ON)
  add_subdirectory(hands-on)
endif()
