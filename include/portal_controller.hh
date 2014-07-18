#ifndef _PORTAL_CONTROLLER_HH_
#define _PORTAL_CONTROLLER_HH_

#include <boost/bind.hpp>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <gazebo/transport/transport.hh>
#include <gazebo/msgs/msgs.hh>
#include "portal_control_request.pb.h"
#include "vector2d.pb.h"
#include <stdio.h>

namespace gazebo
{
  #define CONTROLLABLE_JOINTS 2
  // Typedef for the short form of a boost ptr to our control message type
  typedef const boost::shared_ptr<const portal_control_request_msgs::msgs::PortalControlRequest> PortalControlRequestPtr;

  /// \class PortalController 
  /// \brief Model Plugin to control portal robot joints
  //
  /// This class uses PID-Controllers to control every joint in the portal robot.
  /// You can alter the positions of every joint, by sending a message on the 
  /// "/portal_robot/command" topic. The plugin will update it's loop with the new desired position
  /// and tries to drive the associated joint in that position.
  class PortalController : public ModelPlugin
  {
    // Attributes
    private: physics::JointPtr joints[CONTROLLABLE_JOINTS];
    private: common::PID jointPIDs[CONTROLLABLE_JOINTS];
    private: double jointPositions[CONTROLLABLE_JOINTS];
    private: double jointVelocities[CONTROLLABLE_JOINTS];
    private: double jointMaxEfforts[CONTROLLABLE_JOINTS];
    private: transport::NodePtr node; 
    private: transport::SubscriberPtr commandSubscriber;
    private: transport::SubscriberPtr worldStatsSubscriber;
    private: bool close_gripper;
    private: common::Time prevUpdateTime;
    private: physics::ModelPtr model;
    // Pointer to the update event connection
    private: event::ConnectionPtr updateConnection;

    // Methods
    /// \brief Callback method for every incoming message on the portal robot control topic
    public: void cb(PortalControlRequestPtr &_msg);

    /// \brief Initialize the PID controller, subscribe to the world update calls and subscribe
    /// to the robot control topic
    public: void Load(physics::ModelPtr _parent, sdf::ElementPtr /*_sdf*/);

    /// \brief Callback method for every update in the current world
    ///
    /// This method will calculate the necessary force to control the joints at their desired positions.
    public: void OnUpdate(const common::UpdateInfo & /*_info*/);
  };
  // Register this plugin with the simulator
  GZ_REGISTER_MODEL_PLUGIN(PortalController)
}
#endif
