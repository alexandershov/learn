#include <iostream>

#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;
pthread_cond_t condvar = PTHREAD_COND_INITIALIZER;
int child_exited = 0;

void signal_exit() {
  auto result = pthread_mutex_unlock(&mutex);
  std::cerr << "unlock in child " << result << "\n";
}

void my_join() {
  auto result = pthread_mutex_lock(&mutex);
  std::cerr << "lock in join " << result << "\n";
}

void* child_thread(void* data) {
  std::cerr << "child done\n";
  signal_exit();
  return nullptr;
}

int main() {
  pthread_t child;
  std::cerr << "initial lock " << pthread_mutex_lock(&mutex) << "\n";
  pthread_create(&child, nullptr, child_thread, nullptr);
  my_join();
  std::cerr << "parent done\n";
}
