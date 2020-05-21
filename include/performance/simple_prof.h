// MIT License

// Copyright (c) 2019 Edward Liu

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef PERFORMANCE_SIMPLE_PROF_H_
#define PERFORMANCE_SIMPLE_PROF_H_

#include <unistd.h>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <utility>
#include <vector>

#include "performance/process_info.h"

namespace el_wheel {
namespace performance {

class SimpleTimer {
 public:
  using HighResClock = std::chrono::high_resolution_clock;
  SimpleTimer() : spent_times_(nullptr) { start_ = HighResClock::now(); }
  explicit SimpleTimer(std::vector<int64_t>* const spent_times)
      : spent_times_(spent_times) {
    start_ = HighResClock::now();
  }

  ~SimpleTimer() {
    int64_t duration = std::chrono::duration_cast<std::chrono::microseconds>(
                           HighResClock::now() - start_)
                           .count();
    if (spent_times_) {
      spent_times_->push_back(duration);
    } else {
      std::cout << "Cost time: " << duration << "us" << std::endl;
    }
  }

 private:
  HighResClock::time_point start_;
  std::vector<int64_t>* const spent_times_;
};

class TimerManager {
 public:
  static std::shared_ptr<TimerManager> Instance() {
    if (!instance_) {
      instance_ = std::shared_ptr<TimerManager>(new TimerManager);
    }
    return instance_;
  }

  ~TimerManager();

  std::vector<int64_t>* RegisterTimer(const std::string& block_name);

  enum OutputUnit { kS, kMs, kUs };
  void SetUnit(const OutputUnit unit) { unit_ = unit; }

 private:
  TimerManager() = default;

  std::mutex mutex_;
  std::unordered_map<std::thread::id,
                     std::unordered_map<std::string, std::vector<int64_t>>>
      durations_;

  static std::shared_ptr<TimerManager> instance_;
  OutputUnit unit_ = kUs;

  ProcessProfiler profiler_;
};

}  // namespace performance
}  // namespace el_wheel

#define REGISTER_BLOCK(NAME)                                      \
  auto manager = el_wheel::performance::TimerManager::Instance(); \
  el_wheel::performance::SimpleTimer timer(manager->RegisterTimer(NAME));

#define REGISTER_FUNC REGISTER_BLOCK(__FUNCTION__)

#define SIMPLE_PROF_USE_MS                                  \
  el_wheel::performance::TimerManager::Instance()->SetUnit( \
      el_wheel::performance::TimerManager::OutputUnit::kMs);

#define SIMPLE_PROF_USE_SECOND                              \
  el_wheel::performance::TimerManager::Instance()->SetUnit( \
      el_wheel::performance::TimerManager::OutputUnit::kS);

#endif  // PERFORMANCE_SIMPLE_PROF_H_
