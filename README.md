# Gazebo seminar project: Integration testing with Gazebo
This repository holds the code of our final project for the seminar. The task was:

- Model a world with a portal robot and two objects on it's workspace. The portal robot has 2 DOF and a gripper.
- Write a server side or world plugin plugin that:
  - Controls the robot in a manner, that it picks up one object and stacks it another object
  - Allows to check that a object is laying on another object.
- Write gtest unit tests that start the simulation, and checks if an object has been successfully transfered and placed on the second table
