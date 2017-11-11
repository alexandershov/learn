#include <iostream>
#include <string>
#include <queue>

#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;
pthread_cond_t condvar = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_full_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_empty_cond = PTHREAD_COND_INITIALIZER;
int child_exited = 0;
int NUM_CONSUMERS = 3;
int NUM_PRODUCERS = 10;
int BUFFER_SIZE = 3;

void random_usleep() {
  int duration = std::rand() % 10000;
  usleep(duration);
}

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


std::string make_description(const std::string description, int i) {
  return "thread #" + std::to_string(i) + " " + description;
}

struct thread_data_t {
  std::queue<int>* queue;
  int number;
};

void *consumer_fn(void* bytes) {
  thread_data_t* data = (thread_data_t*)bytes;
  while (true) {
    checked_lock(&mutex, make_description("consumer got lock", data->number));
    while (data->queue->size() == 0) {
      std::cerr << make_description("consumer waiting", data->number) << "\n";
      checked_wait(&not_empty_cond, &mutex, make_description("consumer waited", data->number));
    }
    int item = data->queue->front();
    data->queue->pop();
    checked_signal(&not_full_cond, make_description("consumer signal", data->number));
    std::cerr << make_description("consumer processed ", data->number) << item << "\n";
    checked_unlock(&mutex, make_description("consumer unlock", data->number));
  }
  return nullptr;
}

void *producer_fn(void* bytes) {
  thread_data_t* data = (thread_data_t*)bytes;
  while (true) {
    auto item = std::rand();
    std::cerr << make_description("produced ", data->number) << item << "\n";
    checked_lock(&mutex, make_description("producer got lock", data->number));
    while (data->queue->size() == BUFFER_SIZE) {
      std::cerr << make_description("producer waiting", data->number) << "\n";
      checked_wait(&not_full_cond, &mutex, make_description("producer waited", data->number));
    }
    data->queue->push(item);
    checked_signal(&not_empty_cond, make_description("producer signal", data->number));
    checked_unlock(&mutex, make_description("producer unlock", data->number));
  }
  return nullptr;
}

int main() {
  pthread_t producers[NUM_PRODUCERS];
  pthread_t consumers[NUM_CONSUMERS];
  std::queue<int> queue;
  for (auto i = 0; i < NUM_PRODUCERS; i++) {
    thread_data_t* thread_data = new thread_data_t();
    thread_data->queue = &queue;
    thread_data->number = i;
    pthread_create(&producers[i], nullptr, producer_fn, thread_data);
  }
  for (auto i = 0; i < NUM_CONSUMERS; i++) {
    thread_data_t* thread_data = new thread_data_t();
    thread_data->queue = &queue;
    thread_data->number = i;
    pthread_create(&consumers[i], nullptr, consumer_fn, thread_data);
  }
  sleep(100);
}
