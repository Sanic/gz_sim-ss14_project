#include "gtest/gtest.h"

TEST (SomeTest, Foobaz) { 
    ASSERT_EQ (true, true);
}

TEST (SomeFailingTest, baz) { 
    ASSERT_EQ (1, 2);
}

