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
       // // Get the box and sphere model
       // physics::ModelPtr sphere_model = _world->GetModel("sphere1");
       // physics::ModelPtr box_model = _world->GetModel("box1");
       // 
       // // Apply a small linear velocity to the models
       // sphere_model->SetLinearVel(math::Vector3(.03, 0, 0));
       // box_model->SetLinearVel(math::Vector3(.03, 0, 0));

      // TODO: Use GetModels and match portal_robot* as valid model name
      // We can then delete and re-add models at runtime and the code will still work
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
      // if( portal_robot_model != NULL )
      // {
      //   physics::JointPtr portal_mover_endeffector_mount_joint = portal_robot_model->GetJoint("portal_mover_endeffector_mount");
      //   std::cout << "Joint Angle:" << portal_mover_endeffector_mount_joint->GetAngle(0)->Degree() << std::endl;
      // }
     // std::cout << "The name of the current world: ";
     // std::cout << _world->GetName() << std::endl;
     // physics::PhysicsEnginePtr physics_engine = _world->GetPhysicsEngine ();

     // std::cout << "The physics engine type: ";
     // std::cout << physics_engine->GetType() << std::endl;

     // Subscribe to the World Update event
     this->updateConnection = event::Events::ConnectWorldUpdateBegin(
         boost::bind(&ControlPortal::OnUpdate, this, _1));
    }
}
