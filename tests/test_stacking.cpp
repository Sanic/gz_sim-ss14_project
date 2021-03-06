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

void sleep(int _ms)
{
	boost::this_thread::sleep(boost::posix_time::milliseconds(_ms));
}

void moveBox(int finalSleep)
{
	PortalControllerComm comm;
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
	if (finalSleep > 0)
	{
		sleep(finalSleep);
	}

	// Drive into homepose
	comm.SetEndEffectorHeight(0);
	comm.SetMountRailPosition(0);
}

TEST (StackObject, ShouldSucceed)
{
	gztest::TestClient client("http://localhost:8080");
	ASSERT_TRUE(client.LoadWorld("../worlds/portal_robot_with_bricks"));
	sleep(2000); // sleep 2 seconds to let the gzclient load completely
	gztest::TestHelper th;

	ASSERT_TRUE(th.valueInRange(client.GetPosition("r_box")[1], -0.2, 0.01));
	moveBox(700);
	ASSERT_TRUE(th.valueInRange(client.GetPosition("r_box")[1], 0.25, 0.01));
	boost::function<bool()> check = boost::bind(&gztest::TestClient::OnObject, &client, "r_box", "g_box");
	ASSERT_EQ(th.waitForTrue(check, 10000), true); // Assert r_box is on g_box.
}

TEST (StackObject, ShouldFail)
{
	gztest::TestClient client("http://localhost:8080");
	ASSERT_TRUE(client.LoadWorld("../worlds/portal_robot_with_bricks"));
	sleep(2000); // sleep 2 seconds to let the gzclient load completely
	gztest::TestHelper th;

	// Dont wait for gripper, so moving to initial position should pull the r_box from g_box
	moveBox(0);
	boost::function<bool()> check = boost::bind(&gztest::TestClient::OnObject, &client, "r_box", "g_box");
	ASSERT_EQ(th.waitForTrue(check, 10000), false); // Assert r_box is not on g_box, because it was pulled.
}

TEST (StackObject, ShouldFailToo)
{
	gztest::TestClient client("http://localhost:8080");
	ASSERT_TRUE(client.LoadWorld("../worlds/portal_robot_with_bricks_misplaced"));
	sleep(2000); // sleep 2 seconds to let the gzclient load completely
	gztest::TestHelper th;

	moveBox(0);
	boost::function<bool()> check = boost::bind(&gztest::TestClient::OnObject, &client, "r_box", "g_box");
	ASSERT_EQ(th.waitForTrue(check, 10000), false); // Assert r_box is not on g_box.
}
// 
// TEST (AnotherTest, baz) { 
//     ASSERT_EQ (1, 1);
// }

