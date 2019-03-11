#include "math/math.h"
#include "gtest/gtest.h"

namespace el_wheel {
namespace math {
namespace test {

TEST(TestMath, test_abs) {
  EXPECT_DOUBLE_EQ(1., Abs(1.));
  EXPECT_DOUBLE_EQ(10000000000., Abs(10000000000.));
  EXPECT_DOUBLE_EQ(1., Abs(-1.));
  EXPECT_DOUBLE_EQ(0., Abs(-0.));
  EXPECT_DOUBLE_EQ(std::numeric_limits<double>::max(),
                   Abs(std::numeric_limits<double>::max()));
  EXPECT_DOUBLE_EQ(std::numeric_limits<int>::max(),
                   Abs(std::numeric_limits<int>::max()));
  EXPECT_DOUBLE_EQ(0, Abs<int>(-0));
}

}  // namespace test
}  // namespace math
}  // namespace el_wheel