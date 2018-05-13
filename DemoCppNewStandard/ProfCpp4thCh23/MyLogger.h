#pragma once

#include <queue>
#include <string>
#include <string_view>
#include <thread>
#include <mutex>
#include <condition_variable>

namespace chap23
{
  class MyLogger
  {
  public:
    // Starts a background thread writing log entries to a file.
    MyLogger();

    // Gracefully shut down background thread.
    virtual ~MyLogger();

    // Prevent copy construction and assignment.
    MyLogger(const MyLogger& src) = delete;
    MyLogger& operator=(const MyLogger& rhs) = delete;

    // Add log entry to the queue.
    void log(std::string_view entry);

  private:
    // The function running in the background thread.
    void processEntries();

    // Boolean telling the background thread to terminate.
    bool mExit = false;

    // Mutex and condition variable to protect access to the queue.
    std::mutex mMutex;
    std::condition_variable mCondVar;
    std::queue<std::string> mQueue;

    // The background thread.
    std::thread mThread;
  };
}
