#include "portal_controller_comm.h"

using namespace std;

int main(int argc, char * argv[])
{
    if (argc > 2)
    {
      PortalControllerComm comm;
      int link_id = atoi(argv[1]);
      float value = atof(argv[2]);
      switch(link_id)
      {
        case PC_ENDEFFECTOR_LINK_ID:
          comm.SetEndEffectorHeight(value);
        break;
        case PC_MOUNT_RAIL_LINK_ID: 
          comm.SetMountRailPosition(value);
        break;
        case PC_GRIPPER_LINK_ID: 
          if(value >=0 && value < 1){
            comm.OpenGripper();
          }
          else
          {
            comm.CloseGripper();
          }
        break;
      }
      std::cout << "Command sent" << std::endl;
        return 0;
    }
    else
    {
      std::cout << "Usage: portal_controller_publisher LINK_ID ANGLE/COMMAND" << std::endl;
      std::cout << "link_id 0 = Endeffector mount" << std::endl;
      std::cout << "link_id 1 = Portal rail" << std::endl;
      std::cout << "link_id 2 = Gripper. Use angle=0 to open it, and any other number >=1 to close it." << std::endl;
    }
    return -1;
}
