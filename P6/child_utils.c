#include "child_utils.h"

#define WRITE_END 0
#define READ_END 1
#define MAX_BUFF_SIZE 128

child_process* build_children(int num_children) {
    child_process* pcp = (child_process*) calloc(num_children, sizeof(child_process));
    for(int i = 0; i < num_children; ++i) {
        pcp[i].child_number = i;
    }
    return pcp;

}

int create_pipes(int num_children, child_process* pChildren) {
    int pipe_status = 0;
    for (int i = 0; i < num_children; ++i) {
        pipe_status = pipe(pChildren[i].file_descriptor);
        if (pipe_status == -1) {
            return pipe_status;
        }
    }
    return pipe_status;
}

void non_terminal_child(child_process* pChildprocess, int start_exec_time) {
    int end_time = start_exec_time + 30;
    int n_messages = 1;
    char* BUFF = calloc(MAX_BUFF_SIZE, sizeof(char));
    int message_time;
    double message_millis;
    struct timeval tv;
    gettimeofday(&tv, NULL);

    //close term fds
    close(STDOUT_FILENO);
    close(STDIN_FILENO);

    srand(time(NULL));
    //30 second loop
    while (end_time >= (int)tv.tv_sec) {
        //sleep for 0,2 s
        sleep(rand() % 3);
        gettimeofday(&tv, NULL);
        message_time = (int) (tv.tv_sec - start_exec_time);
        message_millis = (double) (tv.tv_usec / 1000.00);
        //format message
        snprintf(BUFF, MAX_BUFF_SIZE, "%i:%05.3f: Child %i message %i\n", message_time, message_millis, pChildprocess->child_number, n_messages);
        write(pChildprocess->file_descriptor[WRITE_END], BUFF, strlen(BUFF));
        ++n_messages;
    }
    //exit message
    char exit_message[] = "Child process exiting...";
    write(pChildprocess->file_descriptor[WRITE_END], exit_message, sizeof(exit_message));
    close(pChildprocess->file_descriptor[WRITE_END]);
    free(BUFF);
}

void terminal_child(child_process* pChildprocess, int start_exec_time) {
    int end_time = start_exec_time + 30;
    int n_messages = 1;
    char* BUFF = calloc(MAX_BUFF_SIZE, sizeof(char));
    char* user_input = calloc(MAX_BUFF_SIZE, sizeof(char));
    int message_time;
    double message_millis;
    struct timeval tv;
    char user_prompt[] = "Enter input: ";
    //pipe read
    fd_set fdsets;
    struct timeval timeout;
	// set the timeout value
	timeout.tv_sec = 30;
	timeout.tv_usec = 0;

    gettimeofday(&tv, NULL);

    while(end_time >= (int)tv.tv_sec) {
        gettimeofday(&tv, NULL);
        //setup terminal env
        FD_ZERO(&fdsets);
		FD_SET(STDIN_FILENO, &fdsets);
        //write user prompt
        write(STDOUT_FILENO, user_prompt, strlen(user_prompt));
        //monitor for input
        int retval = select(12, &fdsets, NULL, NULL, &timeout);
        //error case
        if(retval == -1) {
            printf("Select error");
        }
        //input case
        else if (retval) {
            gettimeofday(&tv, NULL);
            flush_buff(user_input, MAX_BUFF_SIZE);
            read(STDOUT_FILENO, user_input, MAX_BUFF_SIZE);
            //format the message
            message_time = (int) (tv.tv_sec - start_exec_time);
            message_millis = (double) (tv.tv_usec / 1000.00);
            snprintf(BUFF, MAX_BUFF_SIZE, "%i:%05.3f: Child %i: %d message from terminal: %s", message_time, message_millis, pChildprocess->child_number, n_messages, user_input);
            //write message
            write(pChildprocess->file_descriptor[WRITE_END], BUFF, strlen(BUFF));
            ++n_messages;
            gettimeofday(&tv, NULL);
        }
        else {
            printf("Terminal timeout after 30 seconds\n");
        }
    }
    //exit message
    char exit_message[] = "Child process exiting...";
    write(pChildprocess->file_descriptor[WRITE_END], exit_message, sizeof(exit_message));
    close(pChildprocess->file_descriptor[WRITE_END]);
    free(BUFF);
    free(user_input);
}