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

One way to look at semaphores is: it's a number of free instances of
some resource. When we grab a semaphore this number is decremented (if
there's some free resource of course). When you release a semaphore then
this number is incremented. Good mnemonic is: semaphore(N) will allow
at most N users to use resource.

Recursive mutex can be locked several times by the same thread.
Still you need to unlock it as many times as you locked it.
