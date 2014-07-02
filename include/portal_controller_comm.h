#include <gazebo/transport/transport.hh>
#include <gazebo/msgs/msgs.hh>
#include <gazebo/gazebo.hh>
#include "portal_control_request.pb.h"

#ifndef PORTAL_CONTROLLER_H
#define PORTAL_CONTROLLER_H

// Define link ids of the controllable parts
// and the values to close/open the gripper
// PC = PortalController
#define PC_MOUNT_RAIL_LINK_ID 0
#define PC_ENDEFFECTOR_LINK_ID 1
#define PC_GRIPPER_LINK_ID 2

#define PC_GRIPPER_OPEN 0
#define PC_GRIPPER_CLOSE 1

/*
 * Communication Class for the PortalController
 *
 * This class communicates with the PortalController Plugin
 * that will be loaded when you add a portal_robot to
 * your gazebo world.
 * The communication will be done via gazebo topics
 */
class PortalControllerComm
{
  public: PortalControllerComm();
  public: ~PortalControllerComm();
  private: gazebo::transport::PublisherPtr pub;
  private: portal_control_request_msgs::msgs::PortalControlRequest createRequest(int link_id, float angle);
  public: void closeGripper();
  public: void openGripper();
  public: void setEndEffectorHeight(float value);
  public: void setMountRailPosition(float value);

};
#endif
