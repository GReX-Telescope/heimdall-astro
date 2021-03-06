#ifndef STOPWATCH_HPP
#define STOPWATCH_HPP

#include <chrono>

typedef std::chrono::high_resolution_clock hrclock;
typedef std::chrono::duration<float, std::milli> duration;

class Stopwatch {
  //! Start of measurement
  hrclock::time_point start_time;

  //! Time difference between the last start and stop
  float diff_time;

  //! TOTAL time difference between starts and stops
  float total_time;

  //! flag if the stop watch is running
  bool running;

  //! Number of times clock has been started
  //! and stopped to allow averaging
  int clock_sessions;

public:
  //! Constructor, default
  Stopwatch()
      : start_time(), diff_time(0), total_time(0), running(false),
        clock_sessions(0) {}

  // Destructor
  //~Stopwatch();

  //! Start time measurement
  inline void start();

  //! Stop time measurement
  inline void stop();

  //! Reset time counters to zero
  inline void reset();

  //! Time in msec. after start. If the stop watch is still running (i.e. there
  //! was no call to stop()) then the elapsed time is returned, otherwise the
  //! time between the last start() and stop call is returned
  inline float getTime() const;

  //! Mean time to date based on the number of times the stopwatch has been
  //! _stopped_ (ie finished sessions) and the current total time
  inline float getAverageTime() const;

private:
  // helper functions

  //! Get difference between start time and current time
  inline float getDiffTime() const;
};

// functions, inlined

////////////////////////////////////////////////////////////////////////////////
//! Start time measurement
////////////////////////////////////////////////////////////////////////////////
inline void Stopwatch::start() {
  start_time = hrclock::now();
  running = true;
}

////////////////////////////////////////////////////////////////////////////////
//! Stop time measurement and increment add to the current diff_time summation
//! variable. Also increment the number of times this clock has been run.
////////////////////////////////////////////////////////////////////////////////
inline void Stopwatch::stop() {
  diff_time = getDiffTime();
  total_time += diff_time;
  running = false;
  clock_sessions++;
}

////////////////////////////////////////////////////////////////////////////////
//! Reset the timer to 0. Does not change the timer running state but does
//! recapture this point in time as the current start time if it is running.
////////////////////////////////////////////////////////////////////////////////
inline void Stopwatch::reset() {
  diff_time = 0;
  total_time = 0;
  clock_sessions = 0;
  if (running)
    hrclock::now();
}

////////////////////////////////////////////////////////////////////////////////
//! Time in msec. after start. If the stop watch is still running (i.e. there
//! was no call to stop()) then the elapsed time is returned added to the
//! current diff_time sum, otherwise the current summed time difference alone
//! is returned.
////////////////////////////////////////////////////////////////////////////////
inline float Stopwatch::getTime() const {
  // Return the TOTAL time to date
  float retval = total_time;
  if (running) {

    retval += getDiffTime();
  }

  return retval / (float)1000.0;
}

////////////////////////////////////////////////////////////////////////////////
//! Time in msec. for a single run based on the total number of COMPLETED runs
//! and the total time.
////////////////////////////////////////////////////////////////////////////////
inline float Stopwatch::getAverageTime() const {
  return total_time / clock_sessions;
}

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
inline float Stopwatch::getDiffTime() const {
  duration elapsed = hrclock::now() - start_time;
  // time difference in milli-seconds
  return elapsed.count();
}

#endif // STOPWATCH_H
