#include "portal_controller_comm.h"

//////////////////////////////////////////////////
PortalControllerComm::PortalControllerComm()
{
  gazebo::load();
  gazebo::transport::init();
  gazebo::transport::run();
  gazebo::transport::NodePtr node(new gazebo::transport::Node());

  node->Init("portal_controller_comm");
  this->pub = node->Advertise<portal_control_request_msgs::msgs::PortalControlRequest>("/portal_robot/command");
  pub->WaitForConnection();
}

//////////////////////////////////////////////////
PortalControllerComm::~PortalControllerComm()
{
  gazebo::transport::fini();
}

//////////////////////////////////////////////////
portal_control_request_msgs::msgs::PortalControlRequest PortalControllerComm::CreateRequest(int _linkId, float _angle)
{
  portal_control_request_msgs::msgs::PortalControlRequest request;
  request.set_link_id(_linkId);
  request.set_angle(_angle);
  return request;
}

//////////////////////////////////////////////////
void PortalControllerComm::CloseGripper()
{
  pub->Publish(CreateRequest(PC_GRIPPER_LINK_ID,PC_GRIPPER_CLOSE));
}

//////////////////////////////////////////////////
void PortalControllerComm::OpenGripper(){
  pub->Publish(CreateRequest(PC_GRIPPER_LINK_ID,PC_GRIPPER_OPEN));
}

//////////////////////////////////////////////////
void PortalControllerComm::SetEndEffectorHeight(float _value){
  pub->Publish(CreateRequest(PC_ENDEFFECTOR_LINK_ID, _value));
}

//////////////////////////////////////////////////
void PortalControllerComm::SetMountRailPosition(float _value){
  pub->Publish(CreateRequest(PC_MOUNT_RAIL_LINK_ID, _value));
}
