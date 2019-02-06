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

//keep track of time in seconds
volatile int clock_time;
int MAXIMUM_RUN_TIME = 60;
volatile int tickets_available;


volatile int H_CURRENT_ROW =0;
volatile int H_CURRENT_SEAT = 0;
volatile int M_CURRENT_ROW = 5;
volatile int M_CURRENT_SEAT = 0;
volatile int L_CURRENT_ROW = 9;
volatile int L_CURRENT_SEAT = 0;
volatile int H_CUSTOMERS_WITH_SEATS = 0;
volatile int M_CUSTOMERS_WITH_SEATS = 0;
volatile int L_CUSTOMERS_WITH_SEATS = 0;
volatile int turned_away_customers = 0;


// function to wake up all of the seller threads
void wakeup_all_seller_threads() {
	pthread_mutex_lock(&mutex_condition);
	pthread_cond_broadcast(&cond_go);
	pthread_mutex_unlock(&mutex_condition);
}

void wait_pseudo_hour() {
    while(clock_time < MAXIMUM_RUN_TIME) {
		sleep(1);
		clock_time++;
	}
}
int main(int argc, char* argv[]) {
    printf("Group 1: Matthew Findlay, Kevin Velcich, Esai Morales\n");
    printf("Project 3 Output\n\n\n");

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

    //create string to store seats
	std::string auditorium[10][10];
    //Fill seats with empty placeholder "-"
    createAuditorium(auditorium);
	pthread_t tids[10];
	// create H ticket seller
	Seller* H0 = new Seller(auditorium, "H0", N);
    tids[0] = H0->sellerThread;
	// create 3 M ticket sellers
	for(int i = 1; i < 4; i++) {
		Seller* M = new Seller(auditorium, "M" + std::to_string(i), N);
		tids[i] = M->sellerThread;
	}
	// create 6 L ticket sellers
	for(int i = 4; i < 10; i++) {
		Seller* L = new Seller(auditorium, "L" + std::to_string(i), N);
		tids[i] = L->sellerThread;
	}
    //Sleep to allow threads to create, then wake up at same time
    sleep(5);
	wakeup_all_seller_threads();

    //wait 1 hour (1 minute for us)
    wait_pseudo_hour();

	// wait for all seller threads to exit
	for(int i = 0; i < 10; i++) {
		pthread_join(tids[i], NULL);
	}

  // Printout simulation results …………
    printf("END RESULTS::\n");
	printf("%d H customers seated.\n", H_CUSTOMERS_WITH_SEATS);
	printf("%d M customers seated.\n", M_CUSTOMERS_WITH_SEATS);
	printf("%d L customers seated.\n", L_CUSTOMERS_WITH_SEATS);
	printf("%d customers turned away.\n", turned_away_customers);
	


	exit(0);
}
