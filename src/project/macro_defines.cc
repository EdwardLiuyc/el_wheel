#include <thread>
#include <vector>
#include "project/mutex.h"
#include "project/simple_time.h"

namespace el_wheel {
namespace project {

static char filename[256] = {'\0'};
char* splited_file_name(const char* file) {
  memset(filename, 0, sizeof(filename));
  std::string str = file;
  int index = str.find_last_of('/');
  strcpy(filename, str.substr(index + 1).c_str());

  return filename;
}

struct DebugTimer {
  SimpleTime time;
  std::thread::id thread_id;
};
static std::vector<DebugTimer> debug_start_times;
static project::Mutex mutex;
/*
 * It is a thread-safe clock
 * you can use it in several threads and get the real time spent
 *
 * @warning do not use these clock functions in a section
 * which is locked by MutexLocker
 */
void start_clock() {
  DebugTimer start_time;
  start_time.thread_id = std::this_thread::get_id();
  start_time.time = SimpleTime::get_current_time();
  project::MutexLocker locker(&mutex);
  debug_start_times.push_back(start_time);
}

void end_clock(const char* filename, const char* func_name, const int line) {
  auto current_thread_id = std::this_thread::get_id();
  SimpleTime start_time;
  SimpleTime end_time = SimpleTime::get_current_time();
  bool got_start_time_in_same_thread = false;
  {
    project::MutexLocker locker(&mutex);
    for (auto iter = debug_start_times.rbegin();
         iter != debug_start_times.rend(); ++iter) {
      if (iter->thread_id == current_thread_id) {
        start_time = iter->time;
        got_start_time_in_same_thread = true;
        break;
      }
    }
  }

  if (got_start_time_in_same_thread) {
    PRINT_COLOR_FMT(BOLD, "[ %s: %s: %d ] Cost : %lf s",
                    splited_file_name(filename), func_name, line,
                    (end_time - start_time).toSec());
  } else {
    PRINT_WARNING(
        "Did not find a \"start_clock()\" in current thread, can not calculate "
        "the time cost");
  }
}

// void end_clock_min_time(double min_time) {
//   double spent_time =
//       (SimpleTime::get_current_time() - s_debug_start_time).toSec();
//   if (spent_time > min_time) PRINT_DEBUG_FMT("Cost: %lf s", spent_time);
// }

}  // namespace project
}  // namespace el_wheel
