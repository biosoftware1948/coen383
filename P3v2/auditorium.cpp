#include "auditorium.h"
#include <string.h>
// function to initialize the concert seats
void createAuditorium(std::string s[10][10]) {
	for(int i = 0; i < 10; i++) {
		for(int j = 0; j < 10; j++) {
			s[i][j] = "-";
		}
	}
}

// function to print the concert seating
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

// function to print a customer purchasing a ticket and leaving
void printPurchase(Buyer* b, const char* s) {
	printf("Buyer %i bought fromseller %s\n", b->ID, s);
}

void printTime(int clock) {
    printf("time is 0:%02i", clock);
}

// function to print that the concert is soldout and the customer is turned away
void printSoldout(int clock_time, Buyer* b, const char* s) {
	printf("0:%02i Customer %i has been turned away by seller %s because concert is sold out.\n", clock_time, b->ID, s);
}
