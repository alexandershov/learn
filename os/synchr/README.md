## What is it?
Some code to check pthreads, mutexes, semaphores and condition variables.

## How to run it?
Open the project in CLion.

## Lessons learned
Functions with `_np` suffix in <pthreads.h> are not portable. 
NP - Not Portable.

Printing from several threads into `sys::cout` will lead to interleaved
output. So grab a mutex before printing.

Mac OS X doesn't support `sem_init/sem_destroy`. 
So use named semaphores: `sem_open/sem_close`.
