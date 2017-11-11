#include <iostream>
#include <string>

#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;
pthread_cond_t condvar = PTHREAD_COND_INITIALIZER;
int child_exited = 0;

void checked_lock(pthread_mutex_t* mutex, const std::string& description) {
  auto result = pthread_mutex_lock(mutex);
  std::cerr << description << " lock result " << result << "\n";
}

void checked_unlock(pthread_mutex_t* mutex, const std::string& description) {
  auto result = pthread_mutex_unlock(mutex);
  std::cerr << description << " unlock result " << result << "\n";
}

void signal_exit() {
  checked_unlock(&mutex, "lock in child");
}

void my_join() {
  checked_lock(&mutex, "lock in join");
}

void* child_thread(void* data) {
  std::cerr << "child done\n";
  signal_exit();
  return nullptr;
}

int main() {
  pthread_t child;
  checked_lock(&mutex, "initial lock");
  pthread_create(&child, nullptr, child_thread, nullptr);
  my_join();
  std::cerr << "parent done\n";
}
