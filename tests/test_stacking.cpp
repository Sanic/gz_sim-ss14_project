#include "gtest/gtest.h"
#include <boost/thread.hpp>
#include "portal_controller_comm.h"
#include "gztest/test_helpers.h"
#include "gztest/test_client.h"

/*
 * Use the PortalRobot to stack one object on another
 * and test the correctness.
 * 
 * Please ensure that the Gazebo Master is running the correct world.
 */

void sleep(int _ms){
  boost::this_thread::sleep(boost::posix_time::milliseconds(_ms));
}

TEST (StackObject, ShouldSucceed) { 
  gztest::TestClient client("http://localhost:8080");
  ASSERT_TRUE(client.LoadWorld("/home/moritz/gz_sim-ss14_project/worlds/portal_robot_with_bricks"));
  gztest::TestHelper th;
  PortalControllerComm comm;

  ASSERT_TRUE(th.valueInRange(client.GetPosition("r_box")[1], -0.2, 0.01));

  // Drive to object
  comm.SetMountRailPosition(-0.2f);
  sleep(700);
  comm.SetEndEffectorHeight(-0.5f);
  sleep(700);
  comm.CloseGripper();
  sleep(700);

  // Lift it
  comm.SetEndEffectorHeight(-0.3f);
  sleep(700);
  // Drive to other object
  comm.SetMountRailPosition(0.25f);
  sleep(1500);
  // Put the object down on the other object
  comm.SetEndEffectorHeight(-0.5f);
  sleep(700);
  comm.OpenGripper();

  // Drive into homepose
  comm.SetEndEffectorHeight(0);
  comm.SetMountRailPosition(0);
  ASSERT_TRUE(th.valueInRange(client.GetPosition("r_box")[1], 0.25, 0.01));
  boost::function<bool()> check = boost::bind (&gztest::TestClient::OnObject, &client, "r_box", "g_box");
  ASSERT_EQ (th.waitForTrue(check, 10000), true);
}
// 
// TEST (AnotherTest, baz) { 
//     ASSERT_EQ (1, 1);
// }

