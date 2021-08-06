cmake_minimum_required(VERSION 3.20)

set(MAIN_PROJECT_NAME UTest_Main)

add_executable(${MAIN_PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(${MAIN_PROJECT_NAME} UTest_Core)
target_compile_features(${MAIN_PROJECT_NAME} PUBLIC cxx_std_17)

set_target_properties(${MAIN_PROJECT_NAME} PROPERTIES RUNTIME_OUTPIT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)