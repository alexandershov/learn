#include <iostream>
#include <vector>

#include <cassert>
#include <cstdlib>

#include <linux/futex.h>
#include <pthread.h>

#include <syscall.h>
#include <unistd.h>

const int k_num_threads = 500;

struct thread_data_t {
  int n;
  int *futex;
  int *num_interested_ptr;
};

int futex_wait(int* futex, int value) {
  return syscall(SYS_futex, futex, FUTEX_WAIT, value, NULL, NULL, NULL);
}

int futex_wake(int* futex, int n) {
  return syscall(SYS_futex, futex, FUTEX_WAKE, n, NULL, NULL, NULL);
}

void random_usleep() {
  int duration = std::rand() % 10000;
  usleep(duration);
}

void lock(int *futex, int* num_interested_ptr) {
  random_usleep();
  __sync_fetch_and_add(num_interested_ptr, 1);
  while (__sync_val_compare_and_swap(futex, 0, 1) == 1) {
    random_usleep();
    int wait_result = futex_wait(futex, 1);
    std::cerr << "wait result " << wait_result << "\n";
    random_usleep();
  }
  __sync_fetch_and_add(num_interested_ptr, -1);
}

void unlock(int *futex, int* num_interested_ptr) {
  auto res = __sync_val_compare_and_swap(futex, 1, 0);
  assert(res == 1);
  random_usleep();
  if (*num_interested_ptr) {
    random_usleep();
    futex_wake(futex, 1);
  }
  random_usleep();
}

void *thread_fn(void *bytes) {
  thread_data_t* data = (thread_data_t*)bytes;
  lock(data->futex, data->num_interested_ptr);
  std::cerr << "thread " << data->n << " sleeping\n";
  usleep(10000);
  std::cerr << "thread " << data->n << " done\n";
  unlock(data->futex, data->num_interested_ptr);
  return nullptr;
}

void run_threads() {
  std::vector<pthread_t> threads;
  int *futex = new int(0);
  int *num_interested_ptr = new int(0);
  for (auto i = 0; i < k_num_threads; i++) {
    pthread_t thread;
    thread_data_t *data = new thread_data_t();
    data->n = i;
    data->futex = futex;
    data->num_interested_ptr = num_interested_ptr;
    pthread_create(&thread, nullptr, thread_fn, data);
    threads.push_back(thread);
  }
  for (const auto &thread: threads) {
    pthread_join(thread, nullptr);
  }
}

int main() {
  run_threads();
  std::cerr << "done\n";
}
