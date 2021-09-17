#include <gtest/gtest.h>

TEST(SampleTest, BasicTest1) {
  int64_t a = 1;
  int64_t b = 2;
  EXPECT_EQ(a + b, 3);
}

TEST(SampleTest, BasicTest2) {
  int64_t a = 1;
  int64_t b = 2;
  EXPECT_NE(a + b, 5);
}
