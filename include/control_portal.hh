#ifndef _CONTROL_PORTAL_HH_
#define _CONTROL_PORTAL_HH_

#include "gazebo/gazebo.hh"
#include "gazebo/physics/physics.hh"

namespace gazebo
{
  class ControlPortal : public SystemPlugin
  {
    // Attributes
    private: physics::WorldPtr _world;
    private: event::ConnectionPtr updateConnection;

    public: virtual void Load(int _argc, char** _argv);

    /// \brief Callback method for every update in the current world
    public: void OnUpdate(const common::UpdateInfo & /*_info*/);

    private: virtual void Init();
  };
  // Register this plugin with the simulator
  GZ_REGISTER_SYSTEM_PLUGIN(ControlPortal)
}
#endif
