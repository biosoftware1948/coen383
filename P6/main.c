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
    

    // read from all of the pipes and write to a file
	fd_set fdsets;
	struct timeval timeout;
    // file open
	mode_t mode = S_IRWXU | S_IRWXG | S_IRWXO;
	int file_desc = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, mode);
	if(file_desc < 0) {
		printf("FATAL ERROR: Could not open output.txt");
		return 1;
	}
    // create bool variable to signify a pipe being open
	bool p1 = true, p2 = true, p3 = true, p4 = true, p5 = true;
	// loop as long as a pipe is open
	while(p1 || p2 || p3 || p4 || p5) {
		// set the timeout value
		timeout.tv_sec = 2;
		timeout.tv_usec = 500000;
		// ensure that fds is zeroed
		FD_ZERO(&fdsets);
		// set all of the file descriptors
		for(int i = 0; i < N_CHILDREN; i++) {
			FD_SET(pChildren[i].file_descriptor[READ_END], &fdsets);
		}
		
		int retval = select(12, &fdsets, NULL, NULL, &timeout);
		if(-1 == retval) {
			perror("select()");
		}
		else if(retval) {
			// create a buffer for the message to be read in to
			char* read_msg = malloc(sizeof(char) * MAX_BUFF_SIZE);
			// read from the selected file descriptor and write it to the file
			// first child's pipe
			if(FD_ISSET(pChildren[0].file_descriptor[READ_END], &fdsets)) {
				int val = read_by_line(pChildren[0].file_descriptor[READ_END], read_msg, MAX_BUFF_SIZE);
				// check to see if the pipe has been closed by the child
				if(0 == strcmp("END", read_msg)) {
					// set the pipe open flag to false and close the pipe
					p1 = false;
				}
				// otherwise write the data to the file
				else {
					if('\0' != read_msg[0]) {
						parent_timestamp(file_desc, exec_start_time);
						write_to_file(file_desc, read_msg, val);
					}
				}
			}
			// second child's pipe
			if(FD_ISSET(pChildren[1].file_descriptor[READ_END], &fdsets)) {
				int val = read_by_line(pChildren[1].file_descriptor[READ_END], read_msg, MAX_BUFF_SIZE);
				// check to see if the pipe has been closed by the child
				if(0 == strcmp("END", read_msg)) {
					// set the pipe open flag to false and close the pipe
					p2 = false;
				}
				// otherwise write the data to the file
				else {
					if('\0' != read_msg[0]) {
						parent_timestamp(file_desc, exec_start_time);
						write_to_file(file_desc, read_msg, val);
					}
				}
			}
			// third child's pipe
			if(FD_ISSET(pChildren[2].file_descriptor[READ_END], &fdsets)) {
				int val = read_by_line(pChildren[2].file_descriptor[READ_END], read_msg, MAX_BUFF_SIZE);
				// check to see if the pipe has been closed by the child
				if(0 == strcmp("END", read_msg)) {
					// set the pipe open flag to false and close the pipe
					p3 = false;
				}
				// otherwise write the data to the file
				else {
					if('\0' != read_msg[0]) {
						parent_timestamp(file_desc, exec_start_time);
						write_to_file(file_desc, read_msg, val);
					}
				}
			}
			// fourth child's pipe
			if(FD_ISSET(pChildren[3].file_descriptor[READ_END], &fdsets)) {
				int val = read_by_line(pChildren[3].file_descriptor[READ_END], read_msg, MAX_BUFF_SIZE);
				// check to see if the pipe has been closed by the child
				if(0 == strcmp("END", read_msg)) {
					// set the pipe open flag to false and close the pipe
					p4 = false;
				}
				// otherwise write the data to the file
				else {
					if('\0' != read_msg[0]) {
						parent_timestamp(file_desc, exec_start_time);
						write_to_file(file_desc, read_msg, val);
					}
				}
			}
			// fifth child's pipe
			if(FD_ISSET(pChildren[4].file_descriptor[READ_END], &fdsets)) {
				int val = read_by_line(pChildren[4].file_descriptor[READ_END], read_msg, MAX_BUFF_SIZE);
				// check to see if the pipe has been closed by the child
				if(0 == strcmp("END", read_msg)) {
					// set the pipe open flag to false and close the pipe
					p5 = false;
				}
				// otherwise write the data to the file
				else {
					if('\0' != read_msg[0]) {
						parent_timestamp(file_desc, exec_start_time);
						write_to_file(file_desc, read_msg, val);
					}
				}
			}
			// free the buffer memory
			free(read_msg);
		}
	}
	// close all of the pipes to the children
	for(int i = 0; i < N_CHILDREN; i++) {
		close(pChildren[i].file_descriptor[READ_END]);
	}
	
	// close the output file descriptor
	close(file_desc);
	
	return 0;




}