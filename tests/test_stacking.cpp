#include "gtest/gtest.h"
#include <boost/thread.hpp>
#include "portal_controller_comm.h"

/*
 * Use the PortalRobot to stack one object on another
 * and test the correctness.
 * 
 * Please ensure that the Gazebo Master is running the correct world.
 */

void sleep(int ms){
  boost::this_thread::sleep(boost::posix_time::milliseconds(ms));
}

TEST (StackObject, ShouldSucceed) { 
  PortalControllerComm comm;

  // Drive to object
  comm.setMountRailPosition(-0.2f);
  sleep(700);
  comm.setEndEffectorHeight(-0.5f);
  sleep(700);
  comm.closeGripper();
  sleep(700);

  // Lift it
  comm.setEndEffectorHeight(-0.3f);
  sleep(700);
  // Drive to other object
  comm.setMountRailPosition(0.25f);
  sleep(1500);
  // Put the object down on the other object
  comm.setEndEffectorHeight(-0.5f);
  sleep(700);
  comm.openGripper();
  sleep(700);

  // Drive into homepose
  comm.setEndEffectorHeight(0);
  comm.setMountRailPosition(0);
  // TODO: ASSERT OBJECT r_box on g_box == TRUE

  ASSERT_EQ (true, true);
}
// 
// TEST (AnotherTest, baz) { 
//     ASSERT_EQ (1, 1);
// }

