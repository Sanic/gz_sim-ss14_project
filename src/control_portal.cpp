#include "gazebo/gazebo.hh"
#include "gazebo/physics/physics.hh"
#include "control_portal.hh"

namespace gazebo
{
    //////////////////////////////////////////////////
    void ControlPortal::Load(int _argc, char** _argv)
    {
      // Don't do anything here, because the world will be loaded
      // in Init()!
    }

    //////////////////////////////////////////////////
    void ControlPortal::OnUpdate(const common::UpdateInfo & /*_info*/)
    {
      physics::ModelPtr portal_robot_model = _world->GetModel("portal_robot");
      if( portal_robot_model != NULL )
      {
        physics::JointPtr portal_mover_endeffector_mount_joint = portal_robot_model->GetJoint("portal_mover_endeffector_mount");
        std::cout << "J A,V:" << portal_mover_endeffector_mount_joint->GetAngle(0).Degree();
        std::cout << "," << portal_mover_endeffector_mount_joint->GetVelocity(0) << " ";

        // Hold the endeffector in it's current place
        // portal_mover_endeffector_mount_joint->SetVelocity(0,0); // doesn't keep the EE high
        physics::LinkPtr endeffector_mount_link = portal_robot_model->GetLink("endeffector_mount");
        endeffector_mount_link->SetLinearVel(math::Vector3(0, 0, 0)); // The EE falls slowly down

      }
    }

    //////////////////////////////////////////////////
    void ControlPortal::Init()
    {
      // Get the first world in the simulation
      _world = physics::get_world (); 
      physics::ModelPtr portal_robot_model = _world->GetModel("portal_robot");

     // Subscribe to the World Update event
     this->updateConnection = event::Events::ConnectWorldUpdateBegin(
         boost::bind(&ControlPortal::OnUpdate, this, _1));
    }
}
