/**
 * @author      : Nikita Guzhva (nik_finger@mail.ru)
 * @file        : main
 * @created     : Friday Sep 17, 2021 22:49:46 MSK
 */

#include <chrono>
#include <future>
#include <iostream>
#include <thread>

#include <utils/utils.h>

using namespace std;

class UI {
public:
  UI() {
    uiThread_ = make_unique<thread>(&UI::run, this);
  }

  ~UI() {
    stop();
    uiThread_->join();
  }

  [[nodiscard]] int counter() const {
    return counter_;
  }

  void onFrame() {
    cout << "onFrame started\n";
    sleepForMs(600);
    label_ = counter_ % 2 == 0 ? "Kek" : "Lol";
    cout << "onFrame finished\n";
  }

  void run() {
    while (!shouldStop_) {
      print();
      auto onFrameFuture = async(&UI::onFrame, this);
      sleepForMs(500);
      increment();
    }
  }

  void stop() {
    shouldStop_ = true;
  }

private:
  int counter_ = 0;
  string label_ = "Label";
  mutex mutex_;
  unique_ptr<thread> uiThread_;
  std::atomic_bool shouldStop_ = false;

  void print() {
    lock_guard<mutex> guard(mutex_);
    cout << counter_ << ": " << label_ << "\n";
  }

  void increment() {
    lock_guard<mutex> guard(mutex_);
    ++counter_;
  }
};

int main() {
  UI ui;

  while (ui.counter() < 10) {
    cout << "main\n";
    sleepForMs(1000);
  }

  return 0;
}

