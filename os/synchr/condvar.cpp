#include <iostream>

#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condvar = PTHREAD_COND_INITIALIZER;
int child_exited = 0;

void signal_exit() {
  child_exited = 1;
}

void my_join() {
  while (!child_exited) {
  }
}

void* child_thread(void* data) {
  std::cerr << "child done\n";
  signal_exit();
  return nullptr;
}

int main() {
  pthread_t child;
  pthread_create(&child, nullptr, child_thread, nullptr);
  my_join();
  std::cerr << "parent done\n";
}
