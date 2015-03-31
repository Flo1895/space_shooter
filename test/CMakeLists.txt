# set include dir for all tests
include_directories ("${PROJECT_SOURCE_DIR}/include")

# set include dir for third party testing library
include_directories ("${PROJECT_SOURCE_DIR}/libraries/gtest/include")
include_directories (${PROJECT_COMMON_INCLUDE_DIR})

# specify test cases
# add_executable (Name Name.cpp)
# target_link_libraries (Name LibName gtest_main)
# add_test (Name ${CMAKE_CURRENT_BINARY_DIR}/Name)
