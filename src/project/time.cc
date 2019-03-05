#include "project/time.h"
#include <string>

namespace el_wheel {
namespace project {

project::Duration FromSeconds(const double seconds) {
  return std::chrono::duration_cast<Duration>(
      std::chrono::duration<double>(seconds));
}

double ToSeconds(const Duration duration) {
  return std::chrono::duration_cast<std::chrono::duration<double>>(duration)
      .count();
}

Time FromUniversal(const int64_t ticks) { return Time(Duration(ticks)); }

int64_t ToUniversal(const Time time) { return time.time_since_epoch().count(); }

std::ostream& operator<<(std::ostream& os, const Time time) {
  os << std::to_string(ToUniversal(time));
  return os;
}

project::Duration FromMilliseconds(const int64_t milliseconds) {
  return std::chrono::duration_cast<Duration>(
      std::chrono::milliseconds(milliseconds));
}

}  // namespace project
}  // namespace el_wheel
