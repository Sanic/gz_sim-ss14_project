#include "gtest/gtest.h"
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/thread.hpp>
#include "gztest/test_helpers.h"

TEST (SquareRootTest, Foobar) { 
    ASSERT_EQ (true, true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
