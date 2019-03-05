#include "math/eulers_transform.h"
#include "gtest/gtest.h"

namespace el_wheel {
namespace math {
namespace test {

TEST(TestEularAndTransform, eulers_to_transform) {
  Eigen::Vector3d input(0.1, 0.2, 0.3);
  auto R = EulerAnglesToRotationMatrix(input);
  auto output = RotationMatrixToEulerAngles(R);
  EXPECT_DOUBLE_EQ(input[0], output[0]);
  EXPECT_DOUBLE_EQ(input[1], output[1]);
  EXPECT_DOUBLE_EQ(input[2], output[2]);

  input.setZero();
  output = RotationMatrixToEulerAngles(EulerAnglesToRotationMatrix(input));
  EXPECT_DOUBLE_EQ(input[0], output[0]);
  EXPECT_DOUBLE_EQ(input[1], output[1]);
  EXPECT_DOUBLE_EQ(input[2], output[2]);

  input[0] = M_PI;
  output = RotationMatrixToEulerAngles(EulerAnglesToRotationMatrix(input));
  EXPECT_DOUBLE_EQ(input[0], output[0]);
  EXPECT_DOUBLE_EQ(input[1], output[1]);
  EXPECT_DOUBLE_EQ(input[2], output[2]);

  // can not avoid singularity
}

TEST(TestQuatAndTransform, quaternion_to_transform) {
  Eigen::Quaterniond input(1., 0., 0., 0.);
  input.normalize();
  auto Vector = QuaternionToEulers(input);
  auto output = EulerAnglesToQuaternion(Vector);
  EXPECT_NEAR(input.x(), output.x(), 1.e-10);
  EXPECT_NEAR(input.y(), output.y(), 1.e-10);
  EXPECT_NEAR(input.z(), output.z(), 1.e-10);

  Eigen::Quaterniond input2(1., 0.5, 0.5, 0.);
  input2.normalize();
  Vector = QuaternionToEulers(input2);
  output = EulerAnglesToQuaternion(Vector);
  EXPECT_NEAR(input2.x(), output.x(), 1.e-10);
  EXPECT_NEAR(input2.y(), output.y(), 1.e-10);
  EXPECT_NEAR(input2.z(), output.z(), 1.e-10);

  Eigen::Quaterniond input3(0., 0., 0., 1.);
  input3.normalize();
  Vector = QuaternionToEulers(input3);
  output = EulerAnglesToQuaternion(Vector);
  EXPECT_NEAR(input3.x(), output.x(), 1.e-10);
  EXPECT_NEAR(input3.y(), output.y(), 1.e-10);
  EXPECT_NEAR(input3.z(), output.z(), 1.e-10);
}

}  // namespace test
}  // namespace math
}  // namespace el_wheel