cmake_minimum_required (VERSION 2.6)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra ")

# project name
project (space_shooter)

# specify options
option (BUILD_TESTS
        "Build all tests automatically with the library." OFF)
option (STATIC_SFML
        "Use the static SFML libraries." OFF)

# common dirs and libraries
set (COMMON_INCLUDE_DIR
     "${PROJECT_SOURCE_DIR}/include"
     CACHE INTERNAL
     "Common include directories used by project.")

# set default build type explicitly to Release
if (NOT CMAKE_BUILD_TYPE)
  set (CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build type." FORCE)
endif (NOT CMAKE_BUILD_TYPE)

if (STATIC_SFML)
  set (SFML_STATIC_LIBRARIES TRUE)
endif (STATIC_SFML)

# add sfml
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
set(SFML_ROOT "" CACHE PATH "SFML root directory")
find_package(SFML 2 REQUIRED audio graphics window system)

if(NOT SFML_FOUND)
	message(FATAL_ERROR "SFML couldn't be located!")
endif()

# add subdirectories to build
add_subdirectory (src)

# build tests
if (BUILD_TESTS)
  # this if prevents gtest from being build multiple times
  if (NOT TARGET gtest)
    add_subdirectory (libraries/gtest)
  endif (NOT TARGET gtest)

  enable_testing()
  add_subdirectory(test)
endif (BUILD_TESTS)
