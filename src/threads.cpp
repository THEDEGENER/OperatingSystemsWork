#include <stdio.h>
#include <stdlib.h>
#include "common.hpp"
/*
simple multipthreaded program that demonstrates the issue of races conditions where counter is being incramented concurrently 
and the program has no idea if the counter has been accessed 1 or more times by either worker before the worker incraments the
counter again 
*/


// volatile keyword indicates to the comiler that the variable can be changed 
// asynchronisly by threads other than the current one
volatile int counter = 0;
int loops;

void *worker(void *args) {
    int i;
    for (i = 0; i < loops; i++) {
        counter++;
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: threads <value>\n");
        exit(1);
    };
    // converts a string integer to an integer
    loops = atoi(argv[1]);
    pthread_t p1, p2;
    printf("initial value: %d\n", counter);

    pthread_create(&p1, NULL, worker, NULL);
    pthread_create(&p2, NULL, worker, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    printf("final value: %d\n", counter);
    return 0;
}