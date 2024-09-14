cmake_minimum_required(VERSION 3.23)

set(PROJECT_NAME ecs)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)

file( GLOB SRC src/*.cpp src/core/*.cpp src/core/systems/*.cpp src/core/components/*.cpp)
file (GLOB HEADERS src/*.hpp src/core/*.hpp src/core/systems/*.hpp src/core/components/*.hpp)
file (GLOB CLIENT src/client/*.cpp)
file (GLOB SERVER src/server/*.cpp)

add_executable(${PROJECT_NAME}
        ${SRC}
        ${CLIENT}
        ${HEADERS}
)

add_executable(${PROJECT_NAME}_Server
        ${SRC}
        ${SERVER}
        ${HEADERS}
)

include(build-SFML.cmake)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/assets"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/assets" "${CMAKE_BINARY_DIR}/assets"
)

add_custom_command(
        TARGET ${PROJECT_NAME}_Server POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/assets"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/assets" "${CMAKE_BINARY_DIR}/assets"
)
