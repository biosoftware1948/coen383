#include "file_wrapper.h"

void local_flush_buff(char* msg, int size) {
	for(int i = 0; i < size; i++) {
		msg[i] = '\0';
	}
}

// function to write the parent timestamp to the output message
void parent_timestamp(int fd, int baseTime) {
	// create the struct to use gettimeofday function
	struct timeval tv;
	// get the time of day for the message
	gettimeofday(&tv, NULL);
	// find out the time between messages sent
	int msg_time = (int)(tv.tv_sec - baseTime);
	double msec = (double)(tv.tv_usec/1000.00);
	
	// create a write message buffer
	char* write_msg = malloc(sizeof(char) * 32);
	// format the message that the child will send to the parent
	snprintf(write_msg, 32, "%i:%05.3f: Parent: ", msg_time, msec);
	// write the message to the output file
	write_to_file(fd, write_msg, strlen(write_msg));

    free(write_msg);
}

// this function will read character by character from the
// file descriptor until a new line character is reached
int read_by_line(int fd, char* msg, int size) {
	int value_read = 0;
	// clear the buffer prior to reading
	local_flush_buff(msg, size);
	
	// read no more than the size of the char array
	for(int i = 0; i < size; i++) {
		char c;
		read(fd, &c, 1);
		// if the read character is not NULL add it to the message
		if('\n' != c) {
			msg[i] = c;
			value_read++;
		}
		else {
			msg[i] = c;
			value_read++;
			break;
		}
	}
	return value_read;
}

// this function writes out the data to the desired file
void write_to_file(int fd, char* msg, int size) {
	for(int i = 0; i < size; i++) {
		if('\0' == msg[i]) {
			break;
		}
		else {
			write(fd, &msg[i], 1);
		}
	}
}