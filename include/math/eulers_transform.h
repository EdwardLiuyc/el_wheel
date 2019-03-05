#ifndef EL_WHEEL_MATH_EUAERS_TRANSFORM_H_
#define EL_WHEEL_MATH_EUAERS_TRANSFORM_H_

#include "Eigen/Eigen"

namespace Eigen {
// x, y, z, theta_x, theta_y, theta_z
// 6dof of motion
template <typename Scalar>
using Vector6 = Matrix<Scalar, 6, 1>;
}  // namespace Eigen

namespace el_wheel {
namespace math {

// how to avoid singularity
template <typename T>
Eigen::Matrix<T, 3, 1> RotationMatrixToEulerAngles(
    const Eigen::Matrix<T, 3, 3>& R) {
  auto ret = R.eulerAngles(2, 1, 0);
  Eigen::Matrix<T, 3, 1> result;
  result << ret[2], ret[1], ret[0];

  return result;
}

template <typename T>
Eigen::Quaternion<T> EulerAnglesToQuaternion(
    const Eigen::Matrix<T, 3, 1>& theta) {
  // in general, it is a vector which has 3 member
  /* [ theta_x
       theta_y
       theta_z ] */
  auto& theta_x = theta[0];
  auto& theta_y = theta[1];
  auto& theta_z = theta[2];
  // create rotations
  Eigen::AngleAxis<T> z_angle(theta_z, Eigen::Matrix<T, 3, 1>::UnitZ());
  Eigen::AngleAxis<T> y_angle(theta_y, Eigen::Matrix<T, 3, 1>::UnitY());
  Eigen::AngleAxis<T> x_angle(theta_x, Eigen::Matrix<T, 3, 1>::UnitX());
  Eigen::Quaternion<T> q = z_angle * y_angle * x_angle;

  return q.normalized();
}

template <typename T>
Eigen::Matrix<T, 3, 3> EulerAnglesToRotationMatrix(
    const Eigen::Matrix<T, 3, 1>& theta) {
  return EulerAnglesToQuaternion(theta).toRotationMatrix();
}

template <typename T>
Eigen::Matrix<T, 3, 1> QuaternionToEulers(const Eigen::Quaternion<T>& q) {
  auto R = q.normalized().toRotationMatrix();
  return RotationMatrixToEulerAngles(R);
}

template <typename T>
Eigen::Vector6<T> TransformToVector6(const Eigen::Matrix<T, 4, 4>& t) {
  Eigen::Vector6<T> ret;
  ret.topRows(3) = t.block(0, 3, 3, 1);
  ret.bottomRows(3) =
      RotationMatrixToEulerAngles(Eigen::Matrix<T, 3, 3>(t.block(0, 0, 3, 3)));

  return ret;
}

template <typename T>
Eigen::Matrix<T, 4, 4> Vector6ToTransform(const Eigen::Vector6<T>& v) {
  Eigen::Matrix<T, 4, 4> ret = Eigen::Matrix<T, 4, 4>::Identity();

  ret.template block<3, 1>(0, 3) = v.topRows(3);
  ret.template block<3, 3>(0, 0) =
      EulerAnglesToRotationMatrix(v.bottomRows(3));  // q.toRotationMatrix();

  return ret;
}

}  // namespace math
}  // namespace el_wheel

#endif  // EL_WHEEL_MATH_EUAERS_TRANSFORM_H_