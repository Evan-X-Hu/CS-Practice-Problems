#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>



typedef struct {
    // User defined data may be declaread here.
    int waiting_h; // Counter for hydrogen threads
    int waiting_o; // Counter for oxygen threads
    pthread_mutex_t lock; // Mutex lock, unlocked when not owned by a thread, locked when used by 1 thread
    pthread_cond_t cond_h; // conditional variable for hydrogen thread
    pthread_cond_t cond_o; // conditional variable for oxygen thread
} H2O;

// void releaseHydrogren();
// void releaseOxygen();
// H2O* h2oCreate();
// void hydrogen(H2O* obj);
// void oxygen(H2O* obj);
// void h2oFree(H2O* obj);

void releaseHydrogen() {
    fprintf(stdout, "H");
    return;
}

void releaseOxygen() {
    fprintf(stdout, "O");
    return;
}

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
    pthread_mutex_lock(&obj->lock);
    // 2. Increment waiting_h, acts as if trying to add a hydrogen
    obj->waiting_h++; // For refresher: this actually modifies the value in memory
    // 3. Check if we can form a molecule
    if(obj->waiting_h >= 2 && obj->waiting_o >= 1) { // we can form a molecule
        // We must decrement our variables per each water created
        obj->waiting_h -= 2;
        obj->waiting_o -= 1;

        // Now we must signal 2 hydrogen threads and 1 oxygen thread to release their atoms
        pthread_cond_signal(&obj->cond_h);
        pthread_cond_signal(&obj->cond_h);
        pthread_cond_signal(&obj->cond_o);
    } else { // we cannot form a molecule
        // 4. Wait until we can make a molecule
        pthread_cond_wait(&obj->cond_h, &obj->lock);
    }
    
    // Once we can form a molecule, our thread that detected that has already handled the decrement
    // So now all we need to do is release our atoms
    // releaseHydrogen() outputs "H". Do not change or remove this line.
    releaseHydrogen();

    // 5. Release the lock
    pthread_mutex_unlock(&obj->lock);
    return;
}

void oxygen(H2O* obj) {
    // Repeat what was done for hydrogen here
    // 1. Lock the mutex so that we only run this thread
    pthread_mutex_lock(&obj->lock);
    // 2. Increment waiting_h, acts as if trying to add a hydrogen
    obj->waiting_o++; // For refresher: this actually modifies the value in memory
    // 3. Check if we can form a molecule
    if(obj->waiting_h >= 2 && obj->waiting_o >= 1) { // we can form a molecule
        // We must decrement our variables per each water created
        obj->waiting_h -= 2;
        obj->waiting_o -= 1;

        // Now we must signal 2 hydrogen threads and 1 oxygen thread to release their atoms
        pthread_cond_signal(&obj->cond_h);
        pthread_cond_signal(&obj->cond_h);
        pthread_cond_signal(&obj->cond_o);
    } else { // we cannot form a molecule
        // 4. Wait until we can make a molecule
        pthread_cond_wait(&obj->cond_o, &obj->lock);
    }
    
    // releaseOxygen() outputs "O". Do not change or remove this line.
    releaseOxygen();

    // 5. Release the lock
    pthread_mutex_unlock(&obj->lock);
    return;
}

// A thin wrapper for pthreads, via ChatGPT
void *hydrogen_thread(void *arg) {
    hydrogen((H2O *)arg);  // Cast back to correct type
    return NULL;
}

void *oxygen_thread(void *arg) {
    oxygen((H2O *)arg);  // Cast back to correct type
    return NULL;
}

void h2oFree(H2O* obj) {
    // User defined data may be cleaned up here
    pthread_mutex_destroy(&obj->lock);
    pthread_cond_destroy(&obj->cond_h);
    pthread_cond_destroy(&obj->cond_o);
    free(obj);
    return;
}

// In our main function we need to interpret basic input and loop through a string of chars
int main() {
    char* atoms_buffer = NULL;
    size_t length = 0;
    ssize_t numchars;
    
    // Handle input:
    fprintf(stdout, "Input: water = ");
    if((numchars = getline(&atoms_buffer, &length, stdin)) == -1) {
        fprintf(stderr, "Error: Inputting to atoms_buffer\n");
        free(atoms_buffer);
        return 0;
    }

    // Remove trailing newline
    if(atoms_buffer[numchars - 1] == '\n') {
        atoms_buffer[numchars - 1] = '\0';
    }

    // Initialize our H20 struct
    H2O* h2o_obj = h2oCreate();

    // Initialize our threads based on the size of our input
    pthread_t threads[numchars];


    // Then depending on the char "H" or "O" we must spawn a new thread that will output the
    // "H" or "O" depending on if we are able to create a new water molecule or not
    for(int i=0; i<numchars; i++) { // We could also do a while loop until the null but we need i
        char cur = *atoms_buffer;
        //fprintf(stdout, "TEST: %d\n", cur);
        if(cur == 'H') { // Create new hydrogen thread
            // pthread takes 4 args: (addr of the thread, attributes of the thread [NULL for default], any function's address, the argument to pass into the function)
            pthread_create(&threads[i], NULL, &hydrogen_thread, h2o_obj);
        } else if(cur == 'O') { // Create new oxygen thread
            pthread_create(&threads[i], NULL, &oxygen_thread, h2o_obj);
        } else if(cur == 0) {
            break; // exit for loop preemptively if we reach the null terminator
            // since if we were to loop again we would go past the null terminator
        } else { // We have bad input exit program, this is a problem bc it is faulting at the null terminator
            fprintf(stderr, "Error: Input has irregular format\n");
            h2oFree(h2o_obj); // Free the h2o_obj before exiting
            free(atoms_buffer);
            return 0;
        }

        atoms_buffer++;
    }

    for(int i=0; i<numchars-1; i++) {
        pthread_join(threads[i], NULL); // Join the thread to guarantee it completes
    }

    fprintf(stdout, "\n"); // print a line to make output look nice
    h2oFree(h2o_obj); // Free the h2o_obj before exiting

    return 0;
}