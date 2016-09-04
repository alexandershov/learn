#include <pthread.h>
#include <semaphore.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>


const int NUM_THREADS = 10;
const uint32_t SEM_VALUE = 3;


struct synchr_data_t {
    pthread_mutex_t *mutex;
    sem_t *semaphore;
};


void *do_stuff(void *data) {
    synchr_data_t *s_data = (synchr_data_t *) data;
    auto thread = pthread_self();
    // pthread_mach_thread_np is Mac OS X specific
    auto thread_id = pthread_mach_thread_np(thread);

    if (sem_wait(s_data->semaphore)) {
        std::perror("sem_wait");
    }
    pthread_mutex_lock(s_data->mutex);
    std::cout << "got semaphore! " << thread_id << std::endl;
    pthread_mutex_unlock(s_data->mutex);

    pthread_mutex_lock(s_data->mutex);
    std::cout << "my id = " << thread_id << std::endl;
    pthread_mutex_unlock(s_data->mutex);
    sem_post(s_data->semaphore);
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
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&mutex, &attr);
    data.mutex = &mutex;
    if (pthread_mutex_lock(&mutex)) {
        std::perror("main first mutex_lock");
    }
    std::cout << "got mutex for the first time!" << std::endl;
    if (pthread_mutex_lock(&mutex)) {
        std::perror("main second mutex_lock");
    }
    std::cout << "got mutex twice! because it's recursive." << std::endl;
    pthread_mutex_unlock(&mutex);
//    number of unlocks on recursive mutex should be the same as the number of locks
    pthread_mutex_unlock(&mutex);
    const char *path = "/learn_os_synchr";
    sem_t *semaphore = sem_open(path, O_CREAT, 0644, SEM_VALUE);
    if (semaphore == SEM_FAILED) {
        std::perror("sem_open");
    }
    data.semaphore = semaphore;
    auto all_threads = create_threads(NUM_THREADS, &data);
    join_threads(all_threads);
    pthread_mutex_destroy(&mutex);
    if (sem_close(semaphore)) {
        std::perror("sem_close");
    }
    if (sem_unlink(path)) {
        std::perror("sem_unlink");
    }
}




