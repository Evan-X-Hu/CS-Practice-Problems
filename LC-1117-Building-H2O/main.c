typedef struct {
    // User defined data may be declaread here.

} H2O;

void releaseHydrogren();

void releaseOxygen();

H2O* h2oCreate() {
    H2O* obj = (H2O*) malloc(sizeof(H2O));

    // Initialize user defined data here.

    return obj;
}

void hydrogen(H2O* obj) {

    // releaseHydrogren() outputs "H". Do not change or remove this line.
}

void oxygen(H2O* obj) {

    // releaseOxygen() outputs "O". Do not change or remove this line.
    releaseOxygen();
}

void h2oFree(H2O* obj) {
    // User defined data may be cleaned up here
}