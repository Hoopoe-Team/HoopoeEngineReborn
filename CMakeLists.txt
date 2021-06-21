cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME Hoopoe_Engine)

add_subdirectory(Hoopoe_Core)
add_subdirectory(Hoopoe_Edit)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Hoopoe_Edit)