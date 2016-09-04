#include <pthread.h>
#include <semaphore.h>

#include <iostream>
#include <vector>


const int NUM_THREADS = 10;


struct synchr_data_t {
    pthread_mutex_t *mutex;
    sem_t *semaphore;
};


void *do_stuff(void *data) {
    synchr_data_t *s_data = (synchr_data_t*)data;
    auto thread = pthread_self();
    // pthread_mach_thread_np is Mac OS X specific
    auto thread_id = pthread_mach_thread_np(thread);

    pthread_mutex_lock(s_data->mutex);
    std::cout << "my id = " << thread_id << std::endl;
    pthread_mutex_unlock(s_data->mutex);
    return nullptr;
}

std::vector<pthread_t> create_threads(uint32_t n, synchr_data_t *data) {
    std::vector<pthread_t> all_threads(n);
    for (uint32_t i = 0; i < NUM_THREADS; i++) {
        pthread_t thread;
        pthread_create(&thread, nullptr, do_stuff, data);
        all_threads.push_back(thread);
    }
    return all_threads;
}

void join_threads(std::vector<pthread_t> all_threads) {
    for (pthread_t thread: all_threads) {
        pthread_join(thread, nullptr);
    }
}

int main() {
    synchr_data_t data;
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, nullptr);
    sem_t semaphore;
    data.mutex = &mutex;
    auto all_threads = create_threads(NUM_THREADS, &data);
    join_threads(all_threads);
}




