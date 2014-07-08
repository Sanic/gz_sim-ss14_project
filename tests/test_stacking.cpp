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
  // GazeboTestClient client(new jsonrpc::HttpClient("http://localhost:8080"));
  gztest::TestClient client("http://localhost:8080");
  std::cout << "TEST";
  ASSERT_TRUE(client.OnObject("r_box", "g_box"));
  sleep(10000);
  client.LoadWorld("worlds/test1.sdf");
  //boost::function<bool()> check = boost::bind (client.onObject, "box1", "box2");
  //ASSERT_EQ (th.waitForTrue(check, 10000), true);
}
// 
// TEST (AnotherTest, baz) { 
//     ASSERT_EQ (1, 1);
// }

