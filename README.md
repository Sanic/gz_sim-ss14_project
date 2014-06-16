# Gazebo seminar project: Integration testing with Gazebo
This repository holds the code of our final project for the seminar. The task was:

- Model a world with a portal robot and two objects on it's workspace. The portal robot has 2 DOF and a gripper.
- Write a server side or world plugin plugin that:
  - Controls the robot in a manner, that it picks up one object and stacks it another object
  - Allows to check that a object is laying on another object.
- Write gtest unit tests that start the simulation, and checks if an object has been successfully transfered and placed on the second table
## Usage
- Go to the folder where the repository contents are
- mkdir build/
- cd build
- cmake ..
- make
- cd ..
- Register your build/ folder to your gazebo plugin path:
```
export GAZEBO_PLUGIN_PATH=${GAZEBO_PLUGIN_PATH}:/FULL/PATH/TO/repo/build
```
- You can use build/portal_controller_publisher to control the joints of the portal robot. The first parameter is the joint_id (1 = endeffector mount, 2 = rail) while the second parameter is the angle you want to set the joint to.
