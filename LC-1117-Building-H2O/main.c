#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>




typedef struct {
    // User defined data may be declaread here.
    int waiting_h; // Counter for hydrogen threads
    int waiting_o; // Counter for oxygen threads
    pthread_mutex_t lock; // Mutex lock, unlocked when not owned by a thread, locked when used by 1 thread
    pthread_cond_t cond_h; // 
    pthread_cond_t cond_o;
} H2O;

void releaseHydrogren();

void releaseOxygen();

H2O* h2oCreate() {
    H2O* obj = (H2O*) malloc(sizeof(H2O));
    // Initialize user defined data here.
    obj->waiting_h = 0;
    obj->waiting_o = 0;
    pthread_mutex_init(&obj->lock, NULL);
    pthread_cond_init(&obj->cond_h, NULL);
    pthread_cond_init(&obj->cond_o, NULL);

    return obj;
}

void hydrogen(H2O* obj) {
    // 1. Lock the mutex so that we only run this thread
    // 2. Increment waiting_h, acts as if trying to add a hydrogen
    // 3. Check if we can form a molecule
    //    If we can't (waiting_h < 2 or waiting_o < 1): then we must wait (use a conditional variable)
    // What wait does is it unlocks the mutex, waits for a signal, then locks the mutex
    // It unlocks the mutex so now other threads can be run. But now we are stuck at the wait
    // point where we are waiting on a signal. After the signal is captured, we essentially return
    // to this thread which is why we must relock the mutex
    // 4. Else we can: then we must decrement and release our hydrogen atom and unlock then mutex

    // releaseHydrogren() outputs "H". Do not change or remove this line.
    releaseHydrogren();
}

void oxygen(H2O* obj) {
    // Repeat what was done for hydrogen here
    // releaseOxygen() outputs "O". Do not change or remove this line.
    releaseOxygen();
}

void h2oFree(H2O* obj) {
    // User defined data may be cleaned up here
    pthread_mutex_destroy(&obj->lock);
    pthread_cond_destroy(&obj->cond_h);
    pthread_cond_destroy(&obj->cond_o);
    free(obj);
}

// In our main function we need to interpret basic input and loop through a string of chars
// Then depending on the char "H" or "O" we must spawn a new thread that will output the
// "H" or "O" depending on if we are able to create a new water molecule or not