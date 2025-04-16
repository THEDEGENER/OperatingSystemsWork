#include <iostream>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <fstream>
#include <wait.h>


/* 
    The OS spawns the process in user mode. The OS will add the proccess to the cpu process list and execute the process
    loading the program from disk into ram, clearing all registers and allocating the private virtual memory. the stack and heap are allocated
    and argc and argv will be pushed onto the stack ensuring they are avalible for the lifetime of the main(). The OS begins executing 
    from the begining of the main process and when it returns from the main process the program may be in a zombie state as
    execution has stopped but the OS hasnt cleaned up the process, when this happens however the memory is returned to the OS and the
    process has trully been killed and the CPU continues on executing its instructions
 */
int time_sys_call_read(void);
int time_sys_call_make_doc(void);
int write_file(int count);
int time_to_write_non_async(void);

int main(int argc, char const *argv[])
{
    // The OS begins executing from here and if a sys call is requested the trap instruction will enter the kernal and raise
    // the permission levels and return from the kernal back to user mode and will return a value depending on the success or
    // failure of the instruction 
    if (time_sys_call_read() != 0) {
        perror("timer failed");
        return 1;
    }

    time_sys_call_make_doc();
    time_to_write_non_async();
    return 0;
}



int time_sys_call_read(void) {
    int fd = 0;
    
    char buffer[1];
    struct timespec start, end; 

    double total_time = 0.0;

    for (int i = 0; i < 30; i++) {
        if (clock_gettime(CLOCK_MONOTONIC, &start) != 0) {
            perror("clock get time start");
            return 1;
        }
        ssize_t bytes_read = read(fd, buffer, 0);
        printf("read returned: %zd\n", bytes_read);

        if (clock_gettime(CLOCK_MONOTONIC, &end) != 0) {
            perror("clock get time end");
            return 1;
        }
        double elapsed = (end.tv_sec - start.tv_sec) + 
                         (end.tv_nsec - start.tv_nsec) / 1e9;
        total_time += elapsed;
    }

    double average_time = total_time / 30;
    printf("average time to read was: %f\n", average_time);
    return 0;
}



int time_sys_call_make_doc(void) {

    struct timespec start_f, end_f; 

    double total_time = 0.0;

    for (int i = 20; i < 30; i++) {
        
        int rc = fork();

        if (rc < 0) {
            fprintf(stderr, "fork failed\n");
            exit(1);
        } else if (rc == 0) {
            if (clock_gettime(CLOCK_MONOTONIC, &start_f) != 0) {
                perror("clock get time start");
                return 1;
            }
            write_file(i);
            if (clock_gettime(CLOCK_MONOTONIC, &end_f) != 0) {
                perror("clock get time start");
                return 1;
            }
            double elapsed = (end_f.tv_sec - start_f.tv_sec) + (end_f.tv_nsec - start_f.tv_nsec) / 1e9;
            total_time += elapsed;
            double average_time = total_time / 3;
            printf("average time to write async was: %f\n", average_time);
            exit(0); 
        } else {
            int rc_wait = wait(NULL);
        }

    }
    return 0;
}

int time_to_write_non_async(void) {
    struct timespec start_d, end_d; 

    double total_time = 0.0;

    for (int i = 40; i < 50; i++) {
        if (clock_gettime(CLOCK_MONOTONIC, &start_d) != 0) {
            perror("clock get time start");
            return 1;
        }
        write_file(i);
        if (clock_gettime(CLOCK_MONOTONIC, &end_d) != 0) {
            perror("clock get time start");
            return 1;
        } 

    }

    double elapsed = (end_d.tv_sec - start_d.tv_sec) + (end_d.tv_nsec - start_d.tv_nsec) / 1e9;
            total_time += elapsed;
            double average_time = total_time / 3;
            printf("average time to write was: %f\n", average_time);
    return 0;

}



int write_file(int count) {
    // Opens the file "output.txt" for writing.
    // std::ios::out flag opens it in output mode.
    // std::ios::trunc flag (default for ofstream) clears the file if it already exists.
    std::string filename = "writes/output" + std::to_string(count) + ".txt";

    std::ofstream outFile(filename, std::ios::out | std::ios::trunc);

    // Check if the file was opened successfully
    if (!outFile) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }

    // Write text into the file
    outFile << "Hello, world!" << std::endl;
    outFile << "This file was created because it did not exist before." << std::endl;

    // Close the file
    outFile.close();

    std::cout << "File written successfully." << std::endl;
    return 0;
}

