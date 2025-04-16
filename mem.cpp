#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "common.hpp"

/*
basic program that allocates memory on the stack and shows the memory address of the pointer and the process id
in doing this when running multiple instances of the program we can see that each has a unique pid but the memory address is the same
for both programs, this is because the virtualization of memory has allocated memory to both programs which both share the same virtual strucure 
but will have very different locations in physical memory 
*/

int main(int argc, char *argv[]) {
    int *p = new int;
    assert(p != NULL);
    std::cout << getpid() << "address pointed to by p:" << p << std::endl;

    *p = 0;
    while (1) {
        Spin(1000);
        *p = *p + 1;
        std::cout << getpid() << "p:" << *p << std::endl;
    }
    return 0;
}


