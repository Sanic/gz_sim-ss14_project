#include "gtest/gtest.h"
#include "gztest/test_helpers.h"
#include "gztest/test_client.h"

/*
 *
 *
 * Please ensure that the Gazebo Master is running the correct world.
 */

TEST (WorldLoader, PositiveReplaceWorld)
{
	gztest::TestClient client("http://localhost:8080");
	gztest::TestHelper helper;
	helper.sleep(5000);
	for (int i = 0; i < 2; i++)
	{
		ASSERT_TRUE(client.LoadWorld("/home/moritz/gz_sim-ss14_project/worlds/portal_robot_with_bricks"));
		helper.sleep(10000);
		ASSERT_TRUE(client.LoadWorld("/home/moritz/gz_sim-ss14_project/worlds/two_cylinders"));
		helper.sleep(10000);
	}
}
