#include "auditorium.h"
#include <string.h>

void createAuditorium(std::string s[10][10]) {
	for(int i = 0; i < 10; i++) {
		for(int j = 0; j < 10; j++) {
			s[i][j] = "-";
		}
	}
}

void printAuditorium(std::string a[10][10]) {
	for(int i = 0; i < 10; i++) {
		for(int j = 0; j < 10; j++) {
            if (a[i][j].compare( "-") == 0) {
                printf("|  %s  |", a[i][j].c_str());
            }
            else {
			    printf("| %s|", a[i][j].c_str());
            }
		}
		printf("\n");
	}
}

