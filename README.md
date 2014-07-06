# Gazebo seminar project: Integration testing with Gazebo
This repository holds the code of our final project for the seminar. The task was:

- Model a world with a portal robot and two objects on it's workspace. The portal robot has 2 DOF and a gripper.
- Write a server side or world plugin plugin that:
  - Controls the robot in a manner, that it picks up one object and stacks it another object
  - Allows to check that a object is laying on another object.
- Write gtest unit tests that start the simulation, and checks if an object has been successfully transfered and placed on the second table

## Usage
- Checkout the repository with git clone --recursive , to get the contents of all submodules
- Install the JSON-RPC Library from https://github.com/cinemast/libjson-rpc-cpp
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
- Register your build/ext/gztest/ folder to your gazebo plugin path. This is necessary for gazebo to find the testing plugin from gztest:
```
export GAZEBO_PLUGIN_PATH=${GAZEBO_PLUGIN_PATH}:/FULL/PATH/TO/repo/build/ext/gztest/
```
- You can use build/portal_controller_publisher to control the joints of the portal robot. The first parameter is the link_id (0 = endeffector mount, 1 = rail) while the second parameter is the angle you want to set the joint to. If you set the link_id to 2, you can open or close the gripper. Use the value "0" as the angle to close the gripper, and every other value >=1 to open it.

## Compile and run the tests
The gtest library will be automatically downloaded to this directory, built and linked against the project. If you execute "cmake .. && make" and "./gazebo_ci_test" in the build/ folder, you can run every test defined in tests/.
Please ensure, that only one cpp file in this directoy has a main method. Otherwise you will get errors during compile time.
