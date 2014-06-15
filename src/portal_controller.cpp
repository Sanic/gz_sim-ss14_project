#include <boost/bind.hpp>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <stdio.h>

namespace gazebo
{
  class PortalController : public ModelPlugin
  {
    private: physics::JointPtr joints;
    private: common::PID jointPIDs;
    private: double jointPositions;
    private: double jointVelocities;
    private: double jointMaxEfforts;
    private: bool state_drive_down;

    private: common::Time prevUpdateTime;
    public: void Load(physics::ModelPtr _parent, sdf::ElementPtr /*_sdf*/)
    {
      // Store the pointer to the model
      this->model = _parent;

      // Listen to the update event. This event is broadcast every
      // simulation iteration.
      this->updateConnection = event::Events::ConnectWorldUpdateBegin(
          boost::bind(&PortalController::OnUpdate, this, _1));

      state_drive_down = false;

      // Init PID Controller:
      //                            P    I    D    imax imin
      this->jointPIDs = common::PID(2000, 30.1, 50.01, 1, -1);
      this->jointPositions = 0;
      this->jointVelocities = 0;
      this->jointMaxEfforts = 100;
      // Fill the Joint ptr
      this->joints = this->model->GetJoint("portal_mover_endeffector_mount");
    }

    // Called by the world update start event
    public: void OnUpdate(const common::UpdateInfo & /*_info*/)
    {

      common::Time currTime = this->model->GetWorld()->GetSimTime();
      common::Time stepTime = currTime - this->prevUpdateTime;
      this->prevUpdateTime = currTime; 

      common::Time passed_seconds_for_start(8,0);
      if(currTime > passed_seconds_for_start)
      {
        if(!state_drive_down)
        {
          std::cout << "Init phase over - Drive EE down" << std::endl;
          this->jointPositions = -0.2;
          state_drive_down = true;
        }
      }

      double pos_target = this->jointPositions;
      double pos_curr = this->joints->GetAngle(0).Radian();
      double max_cmd = this->jointMaxEfforts;

      double pos_err = pos_curr - pos_target; // calculate error for PID

      double effort_cmd = this->jointPIDs.Update(pos_err, stepTime);
      effort_cmd = effort_cmd > max_cmd ? max_cmd :
        (effort_cmd < -max_cmd ? -max_cmd : effort_cmd); // calculate max force

      this->joints->SetForce(0, effort_cmd);
      gzdbg << "control [" << pos_curr << "] [" << pos_target << "]" << "effort [ " << effort_cmd << "]";
    }

    // Pointer to the model
    private: physics::ModelPtr model;

    // Pointer to the update event connection
    private: event::ConnectionPtr updateConnection;
  };

  // Register this plugin with the simulator
  GZ_REGISTER_MODEL_PLUGIN(PortalController)
}
      // Apply a small linear velocity to the model.
      // this->model->SetLinearVel(math::Vector3(.03, 0, 0));
      // std::cout << "U2" << std::endl;
      // physics::JointPtr portal_mover_endeffector_mount_joint = this->model->GetJoint("portal_mover_endeffector_mount");
      // std::cout << "J A,V:" << portal_mover_endeffector_mount_joint->GetAngle(0).Degree();
      // std::cout << "," << portal_mover_endeffector_mount_joint->GetVelocity(0) << " ";

      // // Hold the endeffector in it's current place
      // // portal_mover_endeffector_mount_joint->SetVelocity(0,0); // doesn't keep the EE high
      // physics::LinkPtr endeffector_mount_link = this->model->GetLink("endeffector_mount");
      // endeffector_mount_link->SetLinearVel(math::Vector3(0, 0, 0)); // The EE falls slowly down
