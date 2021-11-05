cmake_minimum_required(VERSION 3.10)

# Project name
project(iDSP)

string(TOLOWER ${PROJECT_NAME} LIB_NAME)

# Generate compile_commands.json for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Request C++11 standard features
set(CMAKE_CXX_STANDARD 14)

# Make sure the compiler looks here for Jack source files
if(UNIX)
    include_directories(/usr/local/include)
    link_directories(/usr/local/lib)
endif()


### UNIT TESTS ###

# Enable `make test`
enable_testing()

# Include the source code
include_directories(${PROJECT_SOURCE_DIR}/include/idsp)

# Include the testing framework
include_directories(${PROJECT_SOURCE_DIR}/test/framework)

# Get test source files
file(GLOB TEST_SRCS ${PROJECT_SOURCE_DIR}/test/*.cpp)

# Run through each test file
foreach(testSrc ${TEST_SRCS})
    # Get extension-less file name
    get_filename_component(testFileName ${testSrc} NAME_WE)
    # Make test name
    set(testName ${PROJECT_NAME}_test_${testFileName})
    # Add target
    add_executable(${testName} ${testSrc})
    # Put test executables in their own directory
    set_target_properties(${testName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/test/bin)

    # Add test to execution
    add_test(
        NAME ${testName}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/test/bin
        COMMAND ${testName}
    )
endforeach(testSrc)
