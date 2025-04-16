#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
#include <chrono>
#include <thread>
#include "common.hpp"

/*
A basic look at multipule programs running in what seemingly seems concurent, this is an illusion of virutalising the cpu
into many cpus that share the same resources but are able to execute many programs
*/


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: cpu <string>\n");
        exit(1);
    }
    char *str = argv[1];
    while (1) {
        Spin(1000);
        printf("%s\n", str);
    }
    return 0;
}