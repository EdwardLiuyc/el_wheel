/*!
 * @file simple_time.h
 * @brief header for class SimpleTime, SimpleDuration
 *
 * @author edward.liu
 * @date 2018-10-08
 *
 * @todo add the classes to namespace "common"
 */

#ifndef EL_WHEEL_PROJECT_SIMPLE_TIME_H_
#define EL_WHEEL_PROJECT_SIMPLE_TIME_H_

#include <ostream>
#include <sstream>
#include "macro_defines.h"

namespace el_wheel {
namespace project {

/*!
 * @class SimpleDuration
 * @brief class SimpleDuration
 *
 * it is like the class SimpleTime but it's simpler
 * and the type of params is signed not unsigned
 *
 * @author edward.liu
 */
class SimpleDuration {
 public:
  SimpleDuration() {}
  SimpleDuration(double t) {
    secs = (int32_t)t;
    nsecs = (int32_t)((t - secs) * (1000000000));
  }
  SimpleDuration(int32_t s, int32_t n) : secs(s), nsecs(n) {}
  ~SimpleDuration() {}

  SimpleDuration &operator=(const SimpleDuration &b) {
    this->nsecs = b.nsecs;
    this->secs = b.secs;
    return *this;
  }

  /*!
   * \brief get a SimpleDuration instance from time in ns
   */
  static SimpleDuration fromNSec(int64_t t) {
    return SimpleDuration((int32_t)(t / 1000000000), (int32_t)(t % 1000000000));
  }

  /*!
   * \brief transfrom the SimpleDuration to a int value (ns)
   */
  inline int64_t toNSec() const {
    return ((int64_t)secs * 1000000000 + (int64_t)nsecs);
  }

  int32_t secs;
  int32_t nsecs;

 private:
};

/*!
 * @class SimpleTime
 * @brief class SimpleTime
 *
 * @author edward.liu
 */
class SimpleTime {
 public:
  SimpleTime() : secs(0), nsecs(0), u_judge_range(1000) {}
  SimpleTime(uint32_t s, uint32_t n) : secs(s), nsecs(n), u_judge_range(1000) {}

  ~SimpleTime() {}

  /*!
   * \brief get current system time into a SimpleTime instance
   */
  static SimpleTime get_current_time() {
    // using c++11 stl
    auto t = std::chrono::high_resolution_clock::now();
    auto nano_seconds = t.time_since_epoch().count();
    return SimpleTime(nano_seconds / 1000000000ull,
                      nano_seconds % 1000000000ull);
  }

  /*!
   * \example simple_time.h
   * this is a example for static function in SimpleTime: for_sec(double sec)
   * * 2.03 -> SimpleTime: secs = 2; nsecs = 0.03 * 1000000000;
   * * -2.03 -> SimpleTime: secs = 0; nsecs = 0;
   *
   * this is a example for static function in SimpleTime: fromNSec(double sec)
   * * 2300000000 -> SimpleTime: secs = 2; nsecs = 300000000;
   */
  /*!
   * \brief get a SimpleTime instance from time in second
   */
  static SimpleTime from_sec(double sec) {
    SimpleTime time;

    if (sec < 0.) return time;

    time.secs = (uint32_t)sec;
    time.nsecs = (uint32_t)((sec - time.secs) * 1000000000);
    return time;
  }

  /*!
   * \brief get a SimpleTime instance from time in ns
   */
  static SimpleTime fromNSec(uint64_t t) {
    return SimpleTime((uint32_t)(t / 1000000000), (uint32_t)(t % 1000000000));
  }

  /*!
   * \brief get a SimpleTime instance with the max value
   */
  static SimpleTime TIME_MAX() {
    return SimpleTime((uint32_t)(0xFFFFFFFF), (uint32_t)999999999);
  }

  SimpleTime &operator=(const SimpleTime &b) {
    this->nsecs = b.nsecs;
    this->secs = b.secs;
    return *this;
  }

  bool operator!=(const SimpleTime &b) const { return !((*this) == b); }

  bool operator==(const SimpleTime &b) const {
    int64_t diff = this->toNSec() - b.toNSec();
    int64_t range = u_judge_range;

    if (diff < 0) diff = -diff;
    return (diff <= range);
  }

  /*!
   * \warning there is risk of overflow
   */
  SimpleTime operator+(const SimpleTime &b) const {
    int64_t tmp_nsecs = this->toNSec() + b.toNSec();
    return fromNSec(tmp_nsecs);
  }

  /*!
   * \warning there is risk of overflow
   */
  SimpleTime operator+(const SimpleDuration &b) const {
    int64_t tmp_nsecs = this->toNSec() + b.toNSec();
    return fromNSec(tmp_nsecs);
  }

  /*!
   * \warning there is risk of overflow
   */
  SimpleTime operator-(const SimpleTime &b) const {
    int64_t tmp_nsecs = this->toNSec() - b.toNSec();
    if (tmp_nsecs < 0) {
      PRINT_INFO("Result is set to 0!");
      tmp_nsecs = 0;
    }
    return fromNSec(tmp_nsecs);
  }

  SimpleTime &operator/=(const int &a) {
    if (a == 0) {
      PRINT_ERROR("Div 0! return itself!");
      return *this;
    }

    int div = a;
    if (div < 0) {
      PRINT_WARNING("/a -> /(-a)!");
      div = -div;
    }
    int64_t tmp_nsecs = this->toNSec();
    tmp_nsecs /= div;

    secs = (uint32_t)(tmp_nsecs / 1000000000);
    nsecs = (uint32_t)(tmp_nsecs % 1000000000);

    return *this;
  }

  /*!
   * \warning there is risk of overflow
   */
  SimpleTime &operator+=(const SimpleTime &b) {
    *this = *this + b;
    return *this;
  }

  /*!
   * @todo use the "judge range" in these judgement
   */
  bool operator<(const SimpleTime &b) const { return (toNSec() < b.toNSec()); }
  bool operator<=(const SimpleTime &b) const {
    return (toNSec() <= b.toNSec());
  }
  bool operator>(const SimpleTime &b) const { return (toNSec() > b.toNSec()); }
  bool operator>=(const SimpleTime &b) const {
    return (toNSec() >= b.toNSec());
  }

  friend std::ostream &operator<<(std::ostream &os, SimpleTime t1) {
    os << t1.secs << "s " << t1.nsecs << "ns ";
    return os;
  }

  std::string DebugString() const {
    std::ostringstream out;
    out << secs << "s " << nsecs << "ns ";
    return out.str();
  }

  /*!
   * \brief transfrom the SimpleTime to a double value (seconds)
   */
  inline double toSec() const {
    return (double)this->secs + (double)(this->nsecs * 1.e-9);
  }

  /*!
   * \brief determining if the time euqals zero
   */
  inline bool isZero() const { return (nsecs == 0 && secs == 0); }

  /*!
   * \brief transfrom the SimpleTime to a int value (ns)
   */
  inline int64_t toNSec() const {
    return ((int64_t)secs * 1000000000 + (int64_t)nsecs);
  }

  /*!
   * \brief using usleep to delay
   */
  inline void sleep() {
    std::this_thread::sleep_for(std::chrono::nanoseconds(toNSec()));
  }

  /*!
   * \brief set the time to zero
   */
  inline void zero() { secs = nsecs = 0; }

  uint32_t secs;
  uint32_t nsecs;

 private:
  /*!
   * @brief it is a range when determining if two time are euqal
   * for now, it is set to 1000 (ns)
   *
   * @todo can be set by user
   */
  uint32_t u_judge_range;
};

}  // namespace project
}  // namespace el_wheel

#endif  // EL_WHEEL_PROJECT_SIMPLE_TIME_H_