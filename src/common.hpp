#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
#include <chrono>
#include <thread>
#include <unistd.h>


void Spin(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}