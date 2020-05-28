#include "costmap_2d/periodic_thread.h"

#include <ros/ros.h>

namespace rock {
namespace task {

PeriodicThread::PeriodicThread(double frequency, const std::function<void()>& fun)
  : frequency_(frequency)
  , fun_(fun)
  , is_started_(false) {}

PeriodicThread::~PeriodicThread() {
  thread_.interrupt();
  thread_.join();
}


void PeriodicThread::Run() {
  ros::Rate rate(frequency_);
  while(ros::ok()) {
    fun_();
    rate.sleep();
  }
}

}   //namespace task
}   //namespace rock
