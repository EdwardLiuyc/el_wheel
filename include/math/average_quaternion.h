#ifndef EL_WHEEL_AVERAGE_QUATERNION_H_
#define EL_WHEEL_AVERAGE_QUATERNION_H_

#include <vector>
#include <Eigen/Eigen>

namespace el_wheel {
namespace math {

// refer to link
// http://wiki.unity3d.com/index.php/Averaging_Quaternions_and_Vectors'

template<typename Scalar>
bool AreQuaternionClose( const Eigen::Quaternion<Scalar>& q1, 
                         const Eigen::Quaternion<Scalar>& q2 ) {
  return q1.dot(q2) >= Scalar(0);
}

template<typename Scalar>
Eigen::Quaternion<Scalar> AverageQuaternion( 
  const std::vector<Eigen::Quaternion<Scalar>>& quaternions ) {

  if( quaternions.empty() ) {
    return Eigen::Quaternion<Scalar>::Identity();
  }

  Scalar w = Scalar( 0 );
  Scalar x = Scalar( 0 );
  Scalar y = Scalar( 0 );
  Scalar z = Scalar( 0 );
  for( auto& q : quaternions ) {
    w += q.w();
    x += q.x();
    y += q.y();
    z += q.z();
  }

  return Eigen::Quaternion<Scalar>(w,x,y,z).normalize();
}

} // namespace math
} // namespace el_wheel

#endif // EL_WHEEL_AVERAGE_QUATERNION_H_