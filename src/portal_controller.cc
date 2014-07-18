// #include <boost/bind.hpp>
// #include <gazebo/gazebo.hh>
// #include <gazebo/physics/physics.hh>
// #include <gazebo/common/common.hh>
// #include <gazebo/transport/transport.hh>
// #include <gazebo/msgs/msgs.hh>
// #include "portal_control_request.pb.h"
// #include "vector2d.pb.h"
// 
// 
// #include <stdio.h>
#include "portal_controller.hh"
 
using namespace gazebo;

/////////////////////////////////////////////////
void PortalController::cb(PortalControlRequestPtr &_msg)
{
  // Dump the message contents to stdout.
  int link_id = _msg->link_id();
  std::cout << "Set joint angle of link " << link_id << " to " << _msg->angle() << std::endl;
  if(link_id >= 0 && link_id < CONTROLLABLE_JOINTS)
  {
    this->jointPositions[link_id] = _msg->angle();
    std::cout << this->jointPositions[link_id] << std::endl;
  }
  else
  {
    // The gripper control is available at the highest link_id
    if( link_id >= 0 && link_id == CONTROLLABLE_JOINTS )
    {
      close_gripper = _msg->angle() != 0;
    }
    else
    {
      std::cout << "Link ID out of bounds. Please use 0 or 1" << std::endl;
    }
  }
}

/////////////////////////////////////////////////
void PortalController::Load(physics::ModelPtr _parent, sdf::ElementPtr /*_sdf*/)
{
  // Store the pointer to the model
  this->model = _parent;

  // Listen to the update event. This event is broadcast every
  // simulation iteration.
  this->updateConnection = event::Events::ConnectWorldUpdateBegin(
      boost::bind(&PortalController::OnUpdate, this, _1));

  // Init EndEffector Mount PID Controller
  //                            P    I    D    imax imin
  this->jointPIDs[0] = common::PID(500, 0, 50.01, 1, -1);
  this->jointPositions[0] = 0;
  this->jointVelocities[0] = 0;
  this->jointMaxEfforts[0] = 100;
  // Fill the Joint ptr
  this->joints[0] = this->model->GetJoint("portal_mover_endeffector_mount");

  // Init Portal Mover PID Controller
  //                                 P    I    D    imax imin
  this->jointPIDs[1] = common::PID(200, 30.1, 50.01, 1, -1);
  this->jointPositions[1] = 0;
  this->jointVelocities[1] = 0;
  this->jointMaxEfforts[1] = 30;
  // Fill the Joint ptr
  this->joints[1] = this->model->GetJoint("portal_mover_portal_mover_rail");

  this->close_gripper = false;


  // Subscribe to a gazebo topic
  node = transport::NodePtr(new transport::Node());
  node->Init(this->model->GetName()); 
  commandSubscriber = node->Subscribe("/portal_robot/command", &PortalController::cb, this);
}

/////////////////////////////////////////////////
void PortalController::OnUpdate(const common::UpdateInfo & /*_info*/)
{

  common::Time currTime = this->model->GetWorld()->GetSimTime();
  common::Time stepTime = currTime - this->prevUpdateTime;
  this->prevUpdateTime = currTime; 

  for(int i=0; i < CONTROLLABLE_JOINTS; i++)
  {
    double pos_target = this->jointPositions[i];
    double pos_curr = this->joints[i]->GetAngle(0).Radian();
    double max_cmd = this->jointMaxEfforts[i];

    double pos_err = pos_curr - pos_target; // calculate error for PID

    double effort_cmd = this->jointPIDs[i].Update(pos_err, stepTime);
    effort_cmd = effort_cmd > max_cmd ? max_cmd :
      (effort_cmd < -max_cmd ? -max_cmd : effort_cmd); // calculate max force

    this->joints[i]->SetForce(0, effort_cmd);
    // gzdbg << "control [" << pos_curr << "] [" << pos_target << "]" << "effort [ " << effort_cmd << "]";
  }

  physics::JointPtr left_finger, right_finger;
  left_finger = this->model->GetJoint("palm_left_finger");
  right_finger = this->model->GetJoint("palm_right_finger");
  if(this->close_gripper)
  {
    left_finger->SetForce(0, -2);
    right_finger->SetForce(0, 2);
  }
  else
  {
    left_finger->SetForce(0, 2);
    right_finger->SetForce(0, -2);
  }
}
