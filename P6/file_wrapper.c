#include "file_wrapper.h"

void flush_buff(char* msg, int size) {
	for(int i = 0; i < size; i++) {
		msg[i] = '\0';
	}
}