#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>
#include <pthread.h>
#include <queue>
#include <string>

#include "buyer.h"
#include "auditorium.h"
#include "seller.h"

//global mutexs
pthread_cond_t cond_go = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex_condition = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_sell = PTHREAD_MUTEX_INITIALIZER;


volatile int clock_time;
int max_time = 60;

volatile int tickets_available;

// create variables and a mutex for the seller rows and seller seats
volatile int rowH =0;
volatile int seatH = 0;
volatile int rowM = 5;
volatile int seatM = 0;
volatile int rowL = 9;
volatile int seatL = 0;
volatile int seated_customers_H = 0;
volatile int seated_customers_M = 0;
volatile int seated_customers_L = 0;
volatile int turned_away_customers = 0;

// function to wake up all of the seller threads
void wakeup_all_seller_threads() {
	pthread_mutex_lock(&mutex_condition);
	pthread_cond_broadcast(&cond_go);
	pthread_mutex_unlock(&mutex_condition);
}


int main(int argc, char* argv[]) {
	// initalize the seed for random arrival time
	int seed = time(NULL);
	srand(seed);
	// initialize the clock time to 0
	clock_time = 0;
	// initialize the available number of tickets to 100
	tickets_available = 100;

    if(argc != 2) {
        printf("Please enter N as a command line argument, where N is the number of buyers\n");
        exit(0);
    }
    int N = atoi(argv[1]);
    printf("%d customers entered\n", N);

	// create the 2d array of seats
	std::string auditorium[10][10];
    createAuditorium(auditorium);
	// initialize the seating chart

	// create seller instance array
	Seller* sellers[10];
	// create thread array to store seller threads
	pthread_t tids[10];


	// create H ticket seller
	sellers[0] = new Seller(auditorium, "H0", N);
	tids[0] = sellers[0]->sellerThread;
	// create 3 M ticket sellers
	for(int i = 1; i < 4; i++) {
		sellers[i] = new Seller(auditorium, "M" + std::to_string(i), N);
		tids[i] = sellers[i]->sellerThread;
	}
	// create 6 L ticket sellers
	for(int i = 4; i < 10; i++) {
		sellers[i] = new Seller(auditorium, "L" + std::to_string(i), N);
		tids[i] = sellers[i]->sellerThread;
	}

	// sleep 1 second to make sure all threads have been created and are waiting
	sleep(1);
	wakeup_all_seller_threads();

	// do work on thre threads while incrementing time
	// sleep is here for now as I am unsure how to wait for all of the threads to be waiting on the conditional
	while(clock_time < max_time) {
		sleep(1);
		clock_time++;
	}

	// wait for all seller threads to exit
	for(int i = 0; i < 10; i++) {
		pthread_join(tids[i], NULL);
	}

	// free all of the sellers
	for(int i=0; i<10; i++) {
		delete sellers[i];
	}
	
	printf("There were %i H customers seated.\n", seated_customers_H);
	printf("There were %i M customers seated.\n", seated_customers_M);
	printf("There were %i L customers seated.\n", seated_customers_L);
	printf("There were %i customers turned away.\n", turned_away_customers);
	
	exit(0);
}
