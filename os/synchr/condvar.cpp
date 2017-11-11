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

void checked_wait(pthread_cond_t* condvar, pthread_mutex_t* mutex, const std::string& description) {
  auto result = pthread_cond_wait(condvar, mutex);
  std::cerr << description << " wait result " << result << "\n";
}

void checked_signal(pthread_cond_t* condvar, const std::string& description) {
  auto result = pthread_cond_signal(condvar);
  std::cerr << description << " wait result " << result << "\n";
}

void signal_exit() {
  checked_lock(&mutex, "lock in child");
  child_exited = 1;
  checked_signal(&condvar, "signal in child");
  checked_unlock(&mutex, "unlock in child");
}

void my_join() {
  checked_lock(&mutex, "lock in join");
  while (!child_exited) {
    checked_wait(&condvar, &mutex, "waiting in parent");
  }
  checked_unlock(&mutex, "unlock in join");
}

void* child_thread(void* data) {
  std::cerr << "child exiting ...\n";
  signal_exit();
  return nullptr;
}

int main() {
  pthread_t child;
  pthread_create(&child, nullptr, child_thread, nullptr);
  my_join();
  std::cerr << "parent done\n";
}
