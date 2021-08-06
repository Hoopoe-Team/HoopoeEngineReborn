cmake_minimum_required(VERSION 3.20)

set(CORE_PROJECT_NAME UTest_Core)

set(CORE_PUBLIC_INCLUDE
    include/UTestBase.hpp
    include/UTest.hpp
)

set(CORE_PRIVATE_SRC
    src/UTest.cpp
    src/UTestBase.cpp
)

set(CORE_ALL_SOURCES
    ${CORE_PUBLIC_INCLUDE}
    ${CORE_PRIVATE_INCLUDE}
    ${CORE_PRIVATE_SRC}
)

add_library(${CORE_PROJECT_NAME} STATIC
    ${CORE_ALL_SOURCES}
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
    ${CORE_ALL_SOURCES}
)

target_include_directories(${CORE_PROJECT_NAME} PUBLIC include)
target_include_directories(${CORE_PROJECT_NAME} PRIVATE src)
target_compile_features(${CORE_PROJECT_NAME} PUBLIC cxx_std_17)

add_subdirectory(../../external/spdlog ${CMAKE_CURRENT_BINARY_DIR}/spdlog) #spdlog
target_link_libraries(${CORE_PROJECT_NAME} PRIVATE spdlog)