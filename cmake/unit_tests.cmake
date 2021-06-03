# Create the unit testing executable.
# By using glob, any test source files that are added to test/ will automatically
# be added to the unit testing executable.
file(GLOB_RECURSE TEST_SOURCE_FILES ${CMAKE_SOURCE_DIR}/tests/*.cpp)

find_package(Catch2 REQUIRED)

add_executable(unit_test ${SOURCES_WO_MAIN} ${TEST_SOURCE_FILES})

target_link_libraries(unit_test PRIVATE Catch2::Catch2)

# Enable CMake `make test` support.
enable_testing()
add_test(NAME UnitTests COMMAND unit_tests)
