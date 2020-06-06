cmake_minimum_required(VERSION 3.15)

project(myproject CXX)
include(cmake/project_settings.cmake)

add_library(project_options INTERFACE)
target_compile_options(project_options INTERFACE cxx_std_17)

add_library(project_warnings INTERFACE)

include(cmake/compiler_warnings.cmake)
set_project_warnings(project_warnings)

option(ENABLE_TESTING "Enable test builds" ON)

set(CONAN_EXTRA_REQUIRES "")
set(CONAN_EXTRA_OPTIONS "")

# Add source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})
