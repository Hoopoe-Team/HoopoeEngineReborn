cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME Hoopoe_UTest)

add_subdirectory(UTest_Core)
add_subdirectory(UTest_Main)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT UTest_Main)