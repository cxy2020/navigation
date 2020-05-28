#include "costmap_2d/time_recorder.h"

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "costmap_2d/periodic_thread.h"

using namespace std;

boost::mutex TimeRecorder::mutex_;
TimeRecorder* TimeRecorder::instance_ = nullptr;
TimeRecorder::Destructor TimeRecorder::destructor_;

TimeRecorder::TimeRecorder() : dir_(getenv("HOME"))
{
  dir_ = dir_ + "/time_log/";
  string command = "mkdir -p " + dir_;
  if (0 != access(dir_.c_str(), 0)) {
      // if this folder not exist, create a new one.
      mkdir(dir_.c_str(), S_IRWXU);
  }

  file_name_[G_MAP] = dir_ + "global_map.txt";
  file_name_[G_R1] = dir_ + "global_r1.txt";
  file_name_[G_R2] = dir_ + "global_r2.txt";
  file_name_[G_R3] = dir_ + "global_r3.txt";
  file_name_[G_R4] = dir_ + "global_r4.txt";
  file_name_[G_R5] = dir_ + "global_r5.txt";
  file_name_[G_R6] = dir_ + "global_r6.txt";
  file_name_[G_R7] = dir_ + "global_r7.txt";
  file_name_[G_R8] = dir_ + "global_r8.txt";
  file_name_[G_R9] = dir_ + "global_r9.txt";
  file_name_[G_R10] = dir_ + "global_r10.txt";
  file_name_[G_R11] = dir_ + "global_r11.txt";
  file_name_[G_R12] = dir_ + "global_r12.txt";
  file_name_[G_R13] = dir_ + "global_r13.txt";
  file_name_[G_R14] = dir_ + "global_r14.txt";
  file_name_[G_R15] = dir_ + "global_r15.txt";
  file_name_[G_R16] = dir_ + "global_r16.txt";
  file_name_[G_R17] = dir_ + "global_r17.txt";
  file_name_[G_R18] = dir_ + "global_r18.txt";
  file_name_[G_R19] = dir_ + "global_r19.txt";
  file_name_[G_R20] = dir_ + "global_r20.txt";

  file_name_[G_R21] = dir_ + "global_r21.txt";
  file_name_[G_R22] = dir_ + "global_r22.txt";
  file_name_[G_R23] = dir_ + "global_r23.txt";
  file_name_[G_R24] = dir_ + "global_r24.txt";
  file_name_[G_R25] = dir_ + "global_r25.txt";
  file_name_[G_R26] = dir_ + "global_r26.txt";
  file_name_[G_R27] = dir_ + "global_r27.txt";
  file_name_[G_R28] = dir_ + "global_r28.txt";
  file_name_[G_R29] = dir_ + "global_r29.txt";
  file_name_[G_R30] = dir_ + "global_r30.txt";
  file_name_[G_R31] = dir_ + "global_r31.txt";
  file_name_[G_R32] = dir_ + "global_r32.txt";
  file_name_[G_R33] = dir_ + "global_r33.txt";
  file_name_[G_R34] = dir_ + "global_r34.txt";
  file_name_[G_R35] = dir_ + "global_r35.txt";
  file_name_[G_R36] = dir_ + "global_r36.txt";
  file_name_[G_R37] = dir_ + "global_r37.txt";
  file_name_[G_R38] = dir_ + "global_r37.txt";
  file_name_[G_R39] = dir_ + "global_r39.txt";

  file_name_[L_MAP] = dir_ + "local_map.txt";
  file_name_[L_R1] = dir_ + "local_r1.txt";
  file_name_[L_R2] = dir_ + "local_r2.txt";
  file_name_[L_R3] = dir_ + "local_r3.txt";
  file_name_[L_R4] = dir_ + "local_r4.txt";
  file_name_[L_R5] = dir_ + "local_r5.txt";
  file_name_[L_R6] = dir_ + "local_r6.txt";
  file_name_[L_R7] = dir_ + "local_r7.txt";
  file_name_[L_R8] = dir_ + "local_r8.txt";
  file_name_[L_R9] = dir_ + "local_r9.txt";
  file_name_[L_R10] = dir_ + "local_r10.txt";
  file_name_[L_R11] = dir_ + "local_r11.txt";
  file_name_[L_R12] = dir_ + "local_r12.txt";
  file_name_[L_R13] = dir_ + "local_r13.txt";
  file_name_[L_R14] = dir_ + "local_r14.txt";
  file_name_[L_R15] = dir_ + "local_r15.txt";
  file_name_[L_R16] = dir_ + "local_r16.txt";
  file_name_[L_R17] = dir_ + "local_r17.txt";
  file_name_[L_R18] = dir_ + "local_r18.txt";
  file_name_[L_R19] = dir_ + "local_r19.txt";
  file_name_[L_R20] = dir_ + "local_r20.txt";

  file_name_[L_R21] = dir_ + "local_r21.txt";
  file_name_[L_R22] = dir_ + "local_r22.txt";
  file_name_[L_R23] = dir_ + "local_r23.txt";
  file_name_[L_R24] = dir_ + "local_r24.txt";
  file_name_[L_R25] = dir_ + "local_r25.txt";
  file_name_[L_R26] = dir_ + "local_r26.txt";
  file_name_[L_R27] = dir_ + "local_r27.txt";
  file_name_[L_R28] = dir_ + "local_r28.txt";
  file_name_[L_R29] = dir_ + "local_r29.txt";
  file_name_[L_R30] = dir_ + "local_r30.txt";
  file_name_[L_R31] = dir_ + "local_r31.txt";
  file_name_[L_R32] = dir_ + "local_r32.txt";
  file_name_[L_R33] = dir_ + "local_r33.txt";
  file_name_[L_R34] = dir_ + "local_r34.txt";
  file_name_[L_R35] = dir_ + "local_r35.txt";
  file_name_[L_R36] = dir_ + "local_r36.txt";
  file_name_[L_R37] = dir_ + "local_r37.txt";
  file_name_[L_R38] = dir_ + "local_r37.txt";
  file_name_[L_R39] = dir_ + "local_r39.txt";

  for (int i = 0; i < LAST_INDEX; ++i) {
    cur_buf_indexes_[i] = 0;
    is_finished_record_[i] = false;
    files_[i] = nullptr;
  }

  write_thread_ = new rock::task::PeriodicThread(0.2,
                                                 std::bind(&TimeRecorder::WriteTimeToFile, this));
  write_thread_->start();
}

TimeRecorder::~TimeRecorder()
{
  delete write_thread_;
  for (int i = 0; i < LAST_INDEX; ++i) {
    files_[i]->flush();
    files_[i]->close();
    delete files_[i];
  }
}

void TimeRecorder::WriteTimeToFile()
{

  int cur_index = 0;
  string line[MAX_TIME_NUM];
  for (int i = 0; i < LAST_INDEX; ++i) {
    time_mutex_[i].lock();
    cur_index = cur_buf_indexes_[i];
    for (int j = 0; j < cur_index; ++j) {
      line[i] += to_string(start_t_buf_[i][j]) + " " + to_string(end_t_buf_[i][j]) + " " +
          to_string(diff_t_buf_[i][j]) + "\n";
    }

    if (!is_finished_record_[i]) {
      start_t_buf_[i][0] = start_t_buf_[i][cur_index];
    }
    cur_buf_indexes_[i] = 0;
    time_mutex_[i].unlock();
  }

  for (int i = 0; i < LAST_INDEX; ++i) {
    if (!line[i].empty()) {
      if (nullptr == files_[i]) {
        files_[i] = new std::ofstream(file_name_[i], ios::out);
      }
      *(files_[i]) << line[i];
      files_[i]->flush();
    }
  }
}
