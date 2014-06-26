#include "gtest/gtest.h"
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/thread.hpp>

bool global_bool = true;
// Simple test function for condition checking
bool returnBool(bool b)
{
  std::cout << " -------------- Executed ---------------------";
  return b;
}

bool toggleGlobalBool()
{
  global_bool = !global_bool;
  return global_bool;
}

// Takes a function pointer and a timeout
// The given function will be called every 100 msec, until it returns true
// If the function returns true, waitForTrue returns true.
// Otherwise, the method will return false after msec millseconds
bool waitForTrue(boost::function<bool()> x, int msec)
{
  boost::posix_time::ptime start_time = boost::posix_time::microsec_clock::local_time();
  boost::posix_time::ptime current_time = boost::posix_time::microsec_clock::local_time();
  while( (current_time - start_time).total_milliseconds() < msec)
  {
    if(x())
      return true;
    boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
    current_time = boost::posix_time::microsec_clock::local_time();
  }
  return false;
}


TEST (SquareRootTest, Foobar) { 
    ASSERT_EQ (true, true);
}

TEST (SquareRootTestMeh, Barfoo) { 
    ASSERT_NE (1, 2);
}

TEST (TestWaitFor, returnImmediatelyWithTrue) { 
    ASSERT_TRUE (waitForTrue(boost::bind (returnBool, true), 2000));
}

TEST (TestWaitFor, returnAfterTimeoutWithFalse) { 
    ASSERT_FALSE(waitForTrue(boost::bind (returnBool, false), 4000));
}

// The condition is false in the first iteration
// In the next test, the method should return true and therefore waitForTrue should return true
// This method should wait for around 1000ms
TEST (TestWaitFor, returnBeforeTimeoutWithTrue) { 
    ASSERT_TRUE(waitForTrue(boost::bind (toggleGlobalBool), 4000));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
