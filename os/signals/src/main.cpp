#include <unistd.h>

#include <csignal>
#include <chrono>
#include <iostream>
#include <thread>


void handle_signal(int signal) {
  std::cerr << "got signal " << signal << "\n";
}

int main() {
  std::cerr << "my pid is " << getpid() << "\n";
  // not catchable
  signal(SIGKILL, handle_signal);
  // abort() function
  signal(SIGABRT, handle_signal);
  // give a process a chance to clean up
  signal(SIGTERM, handle_signal);
  // Ctrl-C
  signal(SIGINT, handle_signal);
  // Ctrl-\
  signal(SIGQUIT, handle_signal);
  std::this_thread::sleep_for(std::chrono::seconds(200));
  std::cerr << "exiting\n";
}
