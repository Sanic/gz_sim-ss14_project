## Gazebo seminar project: Integration testing with Gazebo
This repository holds the code of our final project for the seminar. The task was:

- Model a world with a portal robot and two objects on it's workspace. The portal robot has 2 DOF and a gripper.
- Write a server side or world plugin plugin that:
  - Controls the robot in a manner, that it picks up one object and stacks it another object
  - Allows to check that a object is laying on another object.
- Write gtest unit tests that start the simulation, and checks if an object has been successfully transfered and placed on the second table

### Usage
- Checkout the repository with git clone --recursive , to get the contents of all submodules
- Add the portal_robot model to your model database. You can do this by making a symlink to it:
```
cd ~/.gazebo/models
ln -s /FULL/PATH/TO/REPO/models/portal_robot
```
- Go to the folder where the repository contents are
- Build and prepare the project with the following command:
```
mkdir build && cd build && cmake .. && make && export GAZEBO_PLUGIN_PATH=${GAZEBO_PLUGIN_PATH}:`pwd`
```
- In the main directory, start gazebo with a world containing our robot with:
```
gazebo worlds/portal_robot_with_bricks
```
- You can use build/portal_controller_publisher to control the joints of the portal robot. The first parameter is the link_id (0 = endeffector mount, 1 = rail) while the second parameter is the angle you want to set the joint to. If you set the link_id to 2, you can open or close the gripper. Use the value "0" as the angle to close the gripper, and every other value >=1 to open it.

### Compile and run the tests
This project makes use of the gztest library, a gazebo unit test implementation based on Google Test. To execute the tests, add the build/ folder to your GAZEBO_PLUGIN_PATH again and start the gztest TestWrapper:
```
cd build
export GAZEBO_PLUGIN_PATH=${GAZEBO_PLUGIN_PATH}:`pwd`
./ext/gztest/TestWrapper
```
You can also execute the TestWrapper in headless mode:
```
./ext/gztest/TestWrapper -hl
```
The actual tests are then executed by either running make test, or running ./gazebo_ci_test from inside the build directory. If you are done running your test, kill the TestWrapper process by CTRL+C. Otherwise, it will spawn a new gazebo instance instantly in case one of your tests killed the interface and for the proper display of a newly loaded world.

### Version
This project has been compiled and tested against 1.9.5. We used the gazebo that has been shipped with ROS Hydro.
