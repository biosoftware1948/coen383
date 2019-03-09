#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>

#include "child_utils.h"
#include "file_wrapper.h"

#define N_CHILDREN 5
#define N_FILE_DESCRIPTORS 2 //Read and write
#define MAX_BUFF_SIZE 128
#define WRITE_END 0
#define READ_END 1

int main(int argc, char* argv[]) {
    int pipe_status = 0;
    int exec_start_time;
    struct timeval tv;
    
    //get base time of program execution
    gettimeofday(&tv, NULL);
    exec_start_time = tv.tv_sec; 

    //build children and create pipes for them
    child_process* pChildren = build_children(N_CHILDREN);
    pipe_status = create_pipes(N_CHILDREN, pChildren);
    if(pipe_status == -1) {
        printf("FATAL ERROR: PIPE CREATION FAILED\n");
        return 1;
    }

    //Start the fork process to create subprocesses
    for(int i = 0; i < N_CHILDREN; ++i) {
        pChildren[i].pid = fork();
        //parent case
        if (pChildren[i].pid > 0) {
            close(pChildren[i].file_descriptor[WRITE_END]);
        }
        //Child case
        else if (pChildren[i].pid == 0) {
            if (i == 4) {
                terminal_child(&pChildren[i], exec_start_time);
            }
            else {
                non_terminal_child(&pChildren[i], exec_start_time);
            }
            //Child is done work
            _exit(EXIT_SUCCESS);
        }
        //Fatal error, fork failed
        else {
            printf("FATAL ERROR: FORK FAILURE\n");
            return 1;
        }
    }
    printf("exec time: %d\n", exec_start_time);

    return 0;

}