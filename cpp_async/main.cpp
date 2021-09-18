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

class UI {
public:
  void onFrame() {
    std::cout << "onFrame started\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(600));
    if (counter % 2 == 0)
      label = "Kek";
    else
      label = "Lol";
    std::cout << "onFrame finished\n";
  }

  void run() {
    while (true) {
      print();
      auto onFrameFuture = std::async(std::launch::async, &UI::onFrame, this);
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
      increment();
    }
  }

private:
  int counter = 0;
  std::string label = "Label";
  std::mutex mutex;
  cv::Mat frame;

  void print() {
    std::lock_guard<std::mutex> guard(mutex);
    std::cout << counter << ": " << label << "\n";
  }

  void increment() {
    std::lock_guard<std::mutex> guard(mutex);
    ++counter;
  }
};

int main() {
  UI ui;
  std::thread ui_thread(&UI::run, &ui);

  ui_thread.join();

  return 0;
}

