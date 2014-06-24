#include "gtest/gtest.h"

TEST (SquareRootTest, Foobar) { 
    ASSERT_EQ (true, true);
}

TEST (SquareRootTestMeh, must_fail) { 
    ASSERT_EQ (1, 2);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
