cmake_minimum_required(VERSION 3.2)
project(my_project)

# Require c++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED)
# Set module path to cmake/modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")
# Export compile_commands.json for clang-tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(src)

# Glob to find source files
file(GLOB_RECURSE HEADERS ${CMAKE_SOURCE_DIR}/src/*.hpp)
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
# Source files w/o main for tests
file(GLOB_RECURSE SOURCE_WO_MAIN ${CMAKE_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM SOURCE_WO_MAIN ${CMAKE_SOURCE_DIR}/src/main.cpp)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

# External libraries go here
find_package(fmt REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)

# Testing and linting
include(${CMAKE_SOURCE_DIR}/cmake/unit_tests.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/clang_tools.cmake)

# Set compiler warnings for the project
include(${CMAKE_SOURCE_DIR}/cmake/compiler_warnings.cmake)
set_project_warnings(project_warnings)
