cmake_minimum_required(VERSION 3.20)

set(ENGINE_PROJECT_NAME Hoopoe_Core)

set(ENGINE_PUBLIC_INCLUDE
    include/Hoopoe/Application.hpp
    include/Hoopoe/Log.hpp
    include/Hoopoe/Event.hpp
    include/Hoopoe/FileManager.hpp
)

set(ENGINE_PRIVATE_INCLUDE
    src/Hoopoe/Window.hpp
)

set(ENGINE_PRIVATE_SRC
    src/Hoopoe/Application.cpp
    src/Hoopoe/Window.cpp
    src/Hoopoe/FileManager.cpp
)

add_library(${ENGINE_PROJECT_NAME} STATIC
    ${ENGINE_PUBLIC_INCLUDE}
    ${ENGINE_PRIVATE_INCLUDE}
    ${ENGINE_PRIVATE_SRC}
)

target_include_directories(${ENGINE_PROJECT_NAME} PUBLIC include)
target_include_directories(${ENGINE_PROJECT_NAME} PRIVATE src)
target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC cxx_std_17)

add_subdirectory(../external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw) #OPENGL
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glfw)

add_subdirectory(../external/spdlog ${CMAKE_CURRENT_BINARY_DIR}/spdlog) #spdlog
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE spdlog)

add_subdirectory(../external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad) #glad
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glad)

####################################imgui####################################
set(IMGUI_INCLUDE 
    ../external/imgui/imgui.h
    ../external/imgui/backends/imgui_impl_glfw.h
    ../external/imgui/backends/imgui_impl_opengl3.h
)

set(IMGUI_SRC 
../external/imgui/imgui.cpp
../external/imgui/backends/imgui_impl_glfw.cpp
../external/imgui/backends/imgui_impl_opengl3.cpp
../external/imgui/imgui_demo.cpp
../external/imgui/imgui_draw.cpp
../external/imgui/imgui_tables.cpp
../external/imgui/imgui_widgets.cpp
)

add_library(imgui STATIC
${IMGUI_INCLUDE}
${IMGUI_SRC}
)

target_include_directories(imgui PUBLIC ../external)
target_include_directories(imgui PUBLIC ../external/imgui)
target_link_libraries(imgui PRIVATE glad glfw)

target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE imgui)








