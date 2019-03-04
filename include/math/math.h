#ifndef L2L_CALIB_COMMON_MATH_H_
#define L2L_CALIB_COMMON_MATH_H_

#include <cmath>
#include <vector>

namespace calibration {
namespace math {

// Clamps 'value' to be in the range ['min', 'max'].
template <typename T>
T Clamp(const T value, const T min, const T max) {
  if (value > max) {
    return max;
  }
  if (value < min) {
    return min;
  }
  return value;
}

// Calculates 'base'^'exponent'.
template <typename T>
constexpr T Power(T base, int exponent) {
  return (exponent != 0) ? base * Power(base, exponent - 1) : T(1);
}

// Calculates a^2.
template <typename T>
constexpr T Pow2(T a) {
  return Power(a, 2);
}

// Converts from degrees to radians.
constexpr double DegToRad(double deg) { return M_PI * deg / 180.; }

// Converts form radians to degrees.
constexpr double RadToDeg(double rad) { return 180. * rad / M_PI; }

template <typename T>
constexpr T Abs(const T& a) {
  return (a >= T(0) ? a : -a);
}

// Double equal
constexpr bool DoubleEuqal(const double& a, const double& b) {
  return Abs(a - b) < 1.e-6;
}

// Bring the 'difference' between two angles into [-pi; pi].
template <typename T>
T NormalizeAngleDifference(T difference) {
  while (difference > M_PI) {
    difference -= T(2. * M_PI);
  }
  while (difference < -M_PI) {
    difference += T(2. * M_PI);
  }
  return difference;
}

}  // namespace math
}  // namespace calibration

#endif  // L2L_CALIB_COMMON_MATH_H_
