#include <gazebo/transport/transport.hh>
#include <gazebo/msgs/msgs.hh>
#include <gazebo/gazebo.hh>

#include "portal_control_request.pb.h"
#include "vector2d.pb.h"

using namespace std;

int main(int argc, char * argv[])
{
    if (argc > 2)
    {

        // Load gazebo
        gazebo::load(argc, argv);
        portal_control_request_msgs::msgs::PortalControlRequest request;

        request.set_link_id(atoi(argv[1]));
        request.set_angle(atof(argv[2]));

        gazebo::transport::init();
        gazebo::transport::run();
        gazebo::transport::NodePtr node(new gazebo::transport::Node());

        node->Init("portal_controller_publisher");

        std::cout << "Request: " <<
                     " link_id " << request.link_id() <<
                     " angle: " << request.angle() << std::endl;

        gazebo::transport::PublisherPtr pub =
                node->Advertise<portal_control_request_msgs::msgs::PortalControlRequest>("/portal_robot/command");
        // std::cout << "Wait for connection" << std::endl;
        // pub->WaitForConnection();
        while(true)
        {
          std::cout << "pub" << std::endl;
          pub->Publish(request);
          gazebo::common::Time::MSleep(500);
        }
        gazebo::transport::fini();

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
