cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

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
find_package(Boost REQUIRED system filesystem regex)
find_package(Protobuf REQUIRED)

add_subdirectory(msgs)

# Include gazebo dirs and our msgs dirs in build/
include_directories(
  ${GAZEBO_INCLUDE_DIRS}
  ${CMAKE_CURRENT_BINARY_DIR}/msgs
)



add_library(control_portal SHARED src/control_portal.cpp)
target_link_libraries(control_portal ${GAZEBO_libraries} ${OGRE_LIBRARIES})

add_library(portal_controller SHARED src/portal_controller.cpp)
target_link_libraries(portal_controller portal_control_request_msgs ${GAZEBO_libraries} ${OGRE_LIBRARIES})
add_dependencies(portal_controller portal_control_request_msgs)

add_executable(portal_controller_publisher src/portal_controller_publisher.cpp)
target_link_libraries(portal_controller_publisher portal_control_request_msgs ${GAZEBO_LIBRARIES} ${Boost_LIBRARIES} ${PROTOBUF_LIBRARIES} )
add_dependencies(portal_controller_publisher portal_control_request_msgs)
