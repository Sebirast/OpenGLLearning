cmake_minimum_required(VERSION 3.21)

project("OpenGLTest")

include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw
)

include(FetchContent)

FetchContent_GetProperties(glfw)
if(NOT glfw_POPUlATED)
    FetchContent_Populate(glfw)
    add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()

find_package(GLEW)

add_executable(${PROJECT_NAME} Main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC glfw GLEW::GLEW)
target_include_directories(${PROJECT_NAME} PUBLIC glfw GLEW::GLEW)