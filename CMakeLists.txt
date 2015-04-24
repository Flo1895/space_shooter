cmake_minimum_required (VERSION 2.6)

if (${WIN32})
  message ("Build on windows not (yet) supported.")
endif (${WIN32})

# -I/home/flo/SFML-2.1/include -L/home/flo/SFML-2.1/lib
# set compiler and options
if (${UNIX})
  set (CMAKE_CXX_FLAGS "-std=c++0x -Wall -Wextra -I/home/flo/SFML-2.2/include -L/home/flo/SFML-2.2/lib -lsfml-graphics -lsfml-window -lsfml-system"
       CACHE STRING "Flags used by the compiler during all build types.")
endif (${UNIX})

# project name
project (space_shooter)

# add sfml
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
set(SFML_ROOT "/home/flo/SFML-2.2" CACHE PATH "SFML root directory" )
find_package(SFML 2 REQUIRED system window graphics network audio)

# specify options
option (BUILD_TESTS
        "Build all tests automatically with the library." OFF)

# common dirs and libraries
set (COMMON_INCLUDE_DIR
     "${PROJECT_SOURCE_DIR}/include"
     CACHE INTERNAL
     "Common include directories used by project.")

# set default build type explicitly to Debug
if (NOT CMAKE_BUILD_TYPE)
  set (CMAKE_BUILD_TYPE Debug)
endif (NOT CMAKE_BUILD_TYPE)

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
