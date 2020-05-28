#ifndef TIME_RECORDER_H
#define TIME_RECORDER_H

#include <string>
#include <fstream>
#include <assert.h>

#include <boost/thread/mutex.hpp>

#define MAX_TIME_NUM 80
#define MAX_BUF_SIZE 100

enum TimeIndex {
  G_MAP = 0,
  G_L_STATIC = 1,
  G_L_OBS,
  G_L_INF,
  G_R1 = 1,
  G_R2,
  G_R3,
  G_R4,
  G_R5,
  G_R6,
  G_R7,
  G_R8,
  G_R9,
  G_R10,
  G_R11,
  G_R12,
  G_R13,
  G_R14,
  G_R15,
  G_R16,
  G_R17,
  G_R18,
  G_R19,
  G_R20,

  G_R21,
  G_R22,
  G_R23,
  G_R24,
  G_R25,
  G_R26,
  G_R27,
  G_R28,
  G_R29,
  G_R30,
  G_R31,
  G_R32,
  G_R33,
  G_R34,
  G_R35,
  G_R36,
  G_R37,
  G_R38,
  G_R39,

  L_MAP = 40,
  L_L_OBS = 41,
  L_L_RANGE,
  L_L_INF,
  L_R1 = 41,
  L_R2,
  L_R3,
  L_R4,
  L_R5,
  L_R6,
  L_R7,
  L_R8,
  L_R9,
  L_R10,
  L_R11,
  L_R12,
  L_R13,
  L_R14,
  L_R15,
  L_R16,
  L_R17,
  L_R18,
  L_R19,
  L_R20,

  L_R21,
  L_R22,
  L_R23,
  L_R24,
  L_R25,
  L_R26,
  L_R27,
  L_R28,
  L_R29,
  L_R30,
  L_R31,
  L_R32,
  L_R33,
  L_R34,
  L_R35,
  L_R36,
  L_R37,
  L_R38,
  L_R39,

  LAST_INDEX
};

namespace rock {
namespace task {
class PeriodicThread;
}
}

class TimeRecorder
{
public:
  static TimeRecorder* get_instance() {
    boost::mutex::scoped_lock lock(mutex_);
    if (nullptr == instance_) {
      instance_ = new TimeRecorder();
    }
    return instance_;
  }
  inline void start_record(int t_index) {
    struct timeval start;
    gettimeofday(&start, NULL);
    int& cur_buf_index = cur_buf_indexes_[t_index];
    start_t_buf_[t_index][cur_buf_index] = start.tv_sec + double(start.tv_usec) / 1e6;
    boost::mutex::scoped_lock(time_mutex_[t_index]);
    is_finished_record_[t_index] = false;
  }
  inline void end_record(int t_index) {
    struct timeval end;
    gettimeofday(&end, NULL);
    int& cur_buf_index = cur_buf_indexes_[t_index];
    assert(cur_buf_index < MAX_BUF_SIZE);
    end_t_buf_[t_index][cur_buf_index] = end.tv_sec + double(end.tv_usec) / 1e6;
    diff_t_buf_[t_index][cur_buf_index] = end_t_buf_[t_index][cur_buf_index] -
        start_t_buf_[t_index][cur_buf_index];

    boost::mutex::scoped_lock(time_mutex_[t_index]);
    ++cur_buf_index;
    is_finished_record_[t_index] = true;
  }

private:
  class Destructor {
  public:
    Destructor() = default;
    ~Destructor() {
      delete instance_;
    }
  };

  TimeRecorder();

  ~TimeRecorder();

  void WriteTimeToFile();

  static boost::mutex mutex_;
  boost::mutex time_mutex_[MAX_TIME_NUM];

  static TimeRecorder* instance_;
  static Destructor destructor_;

  std::string dir_;
  int cur_buf_indexes_[MAX_TIME_NUM];
  std::string file_name_[MAX_TIME_NUM];
  bool is_finished_record_[MAX_TIME_NUM];

  double start_t_buf_[MAX_TIME_NUM][MAX_BUF_SIZE];
  double end_t_buf_[MAX_TIME_NUM][MAX_BUF_SIZE];
  double diff_t_buf_[MAX_TIME_NUM][MAX_BUF_SIZE];
  std::ofstream* files_[MAX_TIME_NUM];

  rock::task::PeriodicThread* write_thread_;
};

class TimeRecorderCaller {
public:
  TimeRecorderCaller(int time_index) : time_index_(time_index) {
    TimeRecorder::get_instance()->start_record(time_index);
  }

  ~TimeRecorderCaller() {
    TimeRecorder::get_instance()->end_record(time_index_);
  }

private:
  int time_index_;
};

#endif // TIME_RECORDER_H
