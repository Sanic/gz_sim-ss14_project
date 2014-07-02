#include "portal_controller_comm.h"

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

portal_control_request_msgs::msgs::PortalControlRequest PortalControllerComm::createRequest(int link_id, float angle)
{
  portal_control_request_msgs::msgs::PortalControlRequest request;
  request.set_link_id(link_id);
  request.set_angle(angle);
  return request;
}
void PortalControllerComm::closeGripper()
{
  pub->Publish(createRequest(PC_GRIPPER_LINK_ID,PC_GRIPPER_CLOSE));
}
void PortalControllerComm::openGripper(){
  pub->Publish(createRequest(PC_GRIPPER_LINK_ID,PC_GRIPPER_OPEN));
}
void PortalControllerComm::setEndEffectorHeight(float value){
  pub->Publish(createRequest(PC_ENDEFFECTOR_LINK_ID, value));

}
void PortalControllerComm::setMountRailPosition(float value){
  pub->Publish(createRequest(PC_MOUNT_RAIL_LINK_ID, value));
}
// TODO: Destructor
