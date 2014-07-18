#include <gazebo/transport/transport.hh>
#include <gazebo/msgs/msgs.hh>
#include <gazebo/gazebo.hh>
#include "portal_control_request.pb.h"

#ifndef PORTAL_CONTROLLER_COMM_H
#define PORTAL_CONTROLLER_COMM_H

// Define link ids of the controllable parts
// and the values to close/open the gripper
// PC = PortalController
#define PC_ENDEFFECTOR_LINK_ID 0
#define PC_MOUNT_RAIL_LINK_ID 1
#define PC_GRIPPER_LINK_ID 2

#define PC_GRIPPER_OPEN 0
#define PC_GRIPPER_CLOSE 1

/// 
///  \brief Communication class for the portal_robot controller
/// 
///  Communication Class for the PortalController
/// 
///  This class communicates with the PortalController Plugin
///  that will be loaded when you add a portal_robot to
///  your gazebo world.
///  The communication will be done via gazebo topics.
/// 
class PortalControllerComm
{
  /// \brief Instantiate this class and advertise the control topic. The topic is "/portal_robot/command"
  public: PortalControllerComm();
  public: ~PortalControllerComm();
  private: gazebo::transport::PublisherPtr pub;

  /// \brief Create a portal_control_request message from the given parameters
  ///  \param[in] _linkId The ID of the link that should be moved (by applying force on the associated joint). The IDs are defined at the heading of this include file
  ///  \param[in] _angle The value the associated joint should be set to. Can be a real angle for the Endeffector and the mount rail. Should be 0(=open) or 1(=close) for the Gripper
  private: portal_control_request_msgs::msgs::PortalControlRequest CreateRequest(int _linkId, float _angle);

  /// \brief Close the Gripper of the Robot
  public: void CloseGripper();

  /// \brief Open the Gripper of the Robot
  public: void OpenGripper();

  /// \brief Set the position of the Endeffector to _value. The _value represents the desired position of the portal_mover_endeffector_mount joint.
  public: void SetEndEffectorHeight(float _value);

  /// \brief Set the position of the Endeffector mounting on the rail to _value. The _value represents the desired position of the portal_mover_portal_mover_rail joint.
  public: void SetMountRailPosition(float _value);

};
#endif
