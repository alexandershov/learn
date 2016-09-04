#include <pthread.h>

#include <iostream>
#include <vector>


const int NUM_THREADS = 10;


void *do_stuff(void *data) {
    auto thread = pthread_self();
    // pthread_mach_thread_np is Mac OS X specific
    auto thread_id = pthread_mach_thread_np(thread);
    std::cout << "my id = " << thread_id << std::endl;
    return nullptr;
}

int main() {
    do_stuff(nullptr);
    std::vector<pthread_t*> all_threads;
    for (uint32_t i = 0; i < NUM_THREADS; i++) {
        pthread_t thread;
        pthread_create(&thread, nullptr, do_stuff, nullptr);
        all_threads.push_back(&thread);
    }
    for (pthread_t *thread: all_threads) {
        pthread_join(*thread, nullptr);
    }
}


