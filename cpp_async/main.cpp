/**
 * @author      : Nikita Guzhva (nik_finger@mail.ru)
 * @file        : main
 * @created     : Friday Sep 17, 2021 22:49:46 MSK
 */

#include <chrono>
#include <future>
#include <iostream>
#include <thread>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace std;

class UI {
public:
  UI() {
    uiThread = make_unique<thread>(&UI::run, this);
  }

  ~UI() {
    uiThread->join();
  }

  void onFrame() {
    cout << "onFrame started\n";
    sleep(600);
    if (counter % 2 == 0)
      label = "Kek";
    else
      label = "Lol";
    cout << "onFrame finished\n";
  }

  void run() {
    while (true) {
      print();
      auto onFrameFuture = async(&UI::onFrame, this);
      sleep(500);
      increment();
    }
  }

private:
  int counter = 0;
  string label = "Label";
  mutex mutx;
  unique_ptr<thread> uiThread;

  void print() {
    lock_guard<mutex> guard(mutx);
    cout << counter << ": " << label << "\n";
  }

  void increment() {
    lock_guard<mutex> guard(mutx);
    ++counter;
  }

  static void sleep(int64_t milliseconds) {
    this_thread::sleep_for(chrono::milliseconds(milliseconds));
  }
};

int main() {
  UI ui;

  while (true) {
    cout << "main\n";
    this_thread::sleep_for(chrono::seconds(1));
  }

  return 0;
}

