cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
set(PROJECT_NAME_STR gazebo_ci)
project(${PROJECT_NAME_STR} C CXX)

include (FindPkgConfig)
if (PKG_CONFIG_FOUND)
  pkg_check_modules(GAZEBO gazebo)
  pkg_check_modules(OGRE OGRE)
endif()   
include_directories(include)
include_directories(${GAZEBO_INCLUDE_DIRS} ${OGRE_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS} ${OGRE_LIBRARY_DIRS})

# Necessary BOOST packages ...
include(FindBoost)
find_package(Boost REQUIRED system filesystem regex thread)
find_package(Protobuf REQUIRED)
add_subdirectory(msgs)

# Include our msgs dirs in build/
include_directories(${CMAKE_CURRENT_BINARY_DIR}/msgs)

# Download and compile gtest on the fly ... Thanks to:
# https://github.com/snikulov/google-test-examples 

set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/ext)
add_subdirectory(${EXT_PROJECTS_DIR}/gtest)
enable_testing()
include_directories(${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})

add_subdirectory(${EXT_PROJECTS_DIR}/gztest)
include_directories(${EXT_PROJECTS_DIR}/gztest/include ${JSON_RPC_INCLUDES})
set(PROJECT_TEST_NAME ${PROJECT_NAME_STR}_test)

add_library(portal_controller SHARED src/portal_controller.cc)
target_link_libraries(portal_controller portal_control_request_msgs ${GAZEBO_libraries} ${OGRE_LIBRARIES})
add_dependencies(portal_controller portal_control_request_msgs)

add_executable(portal_controller_publisher src/portal_controller_publisher.cc)
#target_link_libraries(portal_controller_publisher portal_control_request_msgs ${GAZEBO_LIBRARIES} ${Boost_LIBRARIES} ${PROTOBUF_LIBRARIES} )
target_link_libraries(portal_controller_publisher portal_controller_comm)
add_dependencies(portal_controller_publisher portal_control_request_msgs)

# PortalControllerComm library
add_library(portal_controller_comm src/portal_controller_comm.cc)
target_link_libraries(portal_controller_comm portal_control_request_msgs ${GAZEBO_LIBRARIES} ${Boost_LIBRARIES} ${PROTOBUF_LIBRARIES} )
add_dependencies(portal_controller_publisher portal_control_request_msgs)

file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/tests/*.cpp)
add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES})
add_dependencies(${PROJECT_TEST_NAME} googletest_project)
target_link_libraries(${PROJECT_TEST_NAME} pthread ${Boost_LIBRARIES} portal_controller_comm gztest)
	target_link_libraries(${PROJECT_TEST_NAME} 
		${GTEST_LIBS_DIR}/libgtest.a
		${GTEST_LIBS_DIR}/libgtest_main.a
)
# Add a single test which is executable via "make test"
add_test(test1 ${PROJECT_TEST_NAME})
