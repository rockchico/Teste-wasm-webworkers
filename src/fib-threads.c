#include <pthread.h>
#include <stdio.h>
#include <emscripten.h>

// https://developers.google.com/web/updates/2018/10/wasm-threads?authuser=0#threads_what_about_workers
// compilação com emscripten
// emcc -O2 -s USE_PTHREADS=1 -s PTHREAD_POOL_SIZE=2 -o fib-threads.js fib-threads.c -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap", "ccall"]' -s ASSERTIONS=1




// Calculate Fibonacci numbers shared function
int fibonacci(int iterations) {
    int     val = 1;
    int     last = 0;

    if (iterations == 0) {
        return 0;
    }
    for (int i = 1; i < iterations; i++) {
        int     seq;

        seq = val + last;
        last = val;
        val = seq;
    }
    return val;
}

long long expensive_function(long long iterations) {
    
    int i = 0; 
    long long l = iterations;
    int r = 0;

    for (i = 0; i <= l; i++) {
        r = (r + l - i) - (r + l + i); // some random calculation here :p
    }
    
    
    return r;
}





// Start function for the background thread
void *bg_func(void *arg) {
    int     *iter = (void *)arg;

    *iter = fibonacci(*iter);
    return arg;
}

void *bg_fibonacci(void *arg) {
    long long     *iter = (void *)arg;

    *iter = fibonacci(*iter);
    return arg;
}

void *bg_expensive_function(void *arg) {
    long long     *iter = (void *)arg;

    *iter = expensive_function(*iter);
    return arg;
}


// Foreground thread and main entry point
int EMSCRIPTEN_KEEPALIVE teste(int argc, char *argv[]) {
    int         fg_val = 54;
    int         bg_val = 100;

    long long   ef_i = 0;
    int         ef_i_val = 100;

    pthread_t   bg_thread;


    // Create the background thread
    if (pthread_create(&bg_thread, NULL, bg_func, &bg_val)) {
        perror("Thread create failed");
        return 1;
    }

    // Create the background thread
    if (pthread_create(&bg_thread, NULL, bg_expensive_function, &ef_i)) {
        perror("Thread create failed");
        return 1;
    }

    

    // Calculate on the foreground thread
    fg_val = fibonacci(fg_val);
    // Wait for background thread to finish
    if (pthread_join(bg_thread, NULL)) {
        perror("Thread join failed");
        return 2;
    }
    // Show the result from background and foreground threads
    printf("Fib(100) is %d, Fib(6 * 9) is %d\n", bg_val, fg_val);
    printf("Expensive Function = %lld\n", ef_i);

    return 0;
}


int EMSCRIPTEN_KEEPALIVE teste2(long long len) {

    long long   ef_i_1 = len;
    long long   ef_i_2 = len;
    long long   ef_i_3 = len;

    pthread_t   bg_thread1;
    pthread_t   bg_thread2;
    pthread_t   bg_thread3;

    printf("ef_i_1 = %lld\n", ef_i_1);
    printf("ef_i_2 = %lld\n", ef_i_2);
    printf("ef_i_3 = %lld\n", ef_i_3);


    // Create the background thread
    if (pthread_create(&bg_thread1, NULL, bg_fibonacci, &ef_i_1)) {
        perror("Thread create failed");
        return 1;
    }

    // Create the background thread
    if (pthread_create(&bg_thread2, NULL, bg_fibonacci, &ef_i_2)) {
        perror("Thread create failed");
        return 1;
    }

    // Create the background thread
    if (pthread_create(&bg_thread3, NULL, bg_fibonacci, &ef_i_3)) {
        perror("Thread create failed");
        return 1;
    }


    // Wait for background thread to finish
    if (pthread_join(bg_thread1, NULL)) {
        perror("Thread join failed");
        return 2;
    }

    if (pthread_join(bg_thread2, NULL)) {
        perror("Thread join failed");
        return 2;
    }

    if (pthread_join(bg_thread3, NULL)) {
        perror("Thread join failed");
        return 2;
    }

    // Show the result from background and foreground threads
    printf("Expensive Function 1 = %lld\n", ef_i_1);
    printf("Expensive Function 2 = %lld\n", ef_i_2);
    printf("Expensive Function 3 = %lld\n", ef_i_3);

    return 0;
}

