cmake_minimum_required(VERSION 3.20)

set(ENGINE_PROJECT_NAME Hoopoe_Core)

set(ENGINE_PUBLIC_INCLUDE
    include/Hoopoe/Application.hpp
    include/Hoopoe/Log.hpp
)

set(ENGINE_PRIVATE_SRC
    src/Hoopoe/Application.cpp
)

add_library(${ENGINE_PROJECT_NAME} STATIC
    ${ENGINE_PUBLIC_INCLUDE}
    ${ENGINE_PRIVATE_SRC}
)

target_include_directories(${ENGINE_PROJECT_NAME} PUBLIC include)
target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC cxx_std_17)

add_subdirectory(../external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw) #OPENGL
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glfw)

