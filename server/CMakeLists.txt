#
# Configure CMake environment
#

cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

# Include cmake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Include custom cmake modules
include(cmake/HealthCheck.cmake)
include(cmake/CompileOptions.cmake)


# 
# Declare project
# 

# Declare project
project(SelfawareMonopoly C CXX)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(IDE_FOLDER "")


# 
# Project configuration options
# 

option(OPTION_BUILD_TESTS "Build tests." ON)
enable_cppcheck(On)


# 
# External dependencies
# 

find_package(Qt5Core       5.10 REQUIRED)
find_package(Qt5Gui        5.10 REQUIRED)
find_package(Qt5Network    5.10 REQUIRED)
find_package(Qt5Sql        5.10 REQUIRED)
find_package(Qt5Test       5.10 REQUIRED)
find_package(Qt5Widgets    5.10 REQUIRED)
find_package(Qt5WebSockets 5.10 REQUIRED)


# 
# Project modules
# 

add_subdirectory(source)
add_subdirectory(tests)
