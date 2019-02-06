#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <queue>
#include <string>
#include <unistd.h>
#include <pthread.h>
#include <vector>
#include <cassert>

#include "buyer.h"
#include "auditorium.h"
#include "seller.h"

//global mutexs
pthread_cond_t cond_go = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex_condition = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t selling_mutex = PTHREAD_MUTEX_INITIALIZER;

//For the purpose of this simulation we
//pretend that hours are seconds
//so each tick of the clock is 1s real time
//representing 1m of sim time
volatile int timer = 0;
int MAXIMUM_RUN_TIME = 60;
volatile int tickets_for_sale = 100; //100 seats
//Some globals for the threads
//Basically holding current row, seat that the threads
//are gonna try to get
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

std::vector<Seller *> s;

//wait an hour
//this spins for 1 minute
//which is our simulation fo hour
void wait_pseudo_hour() {
    assert(s.size() == 10);

    while(timer < MAXIMUM_RUN_TIME) {
        for (int i = 0; i < s.size(); i++)
            s[i]->printAvailables(timer);
			
        sleep(1);
        timer++;
    }
}

// function to wake up all of the seller threads
void wakeup_all_seller_threads() {
	pthread_mutex_lock(&mutex_condition);
	pthread_cond_broadcast(&cond_go);
	pthread_mutex_unlock(&mutex_condition);
}

int main(int argc, char* argv[]) {
    printf("Group 1: Matthew Findlay, Kevin Velcich, Esai Morales\n");
    printf("Project 3 Output\n\n\n");

    //Get N customers from command line
    if(argc != 2) {
        printf("Please enter N as a command line argument, where N is the number of buyers\n");
        exit(0);
    }
    int N = atoi(argv[1]);
    printf("%d customers entered\n", N);

    //creat the auditorium where seats are
	std::string auditorium[10][10];
    //Fill seats with empty placeholder "-"
    createAuditorium(auditorium);
	pthread_t tids[10];
	// create H ticket seller
	Seller* H0 = new Seller(auditorium, "H0", N);
        s.push_back(H0);
    H0->StartSelling();
    tids[0] = H0->sellerThread;
	// create M ticket sellers
	for(int i = 1; i < 4; i++) {
		Seller* M = new Seller(auditorium, "M" + std::to_string(i), N);
        M->StartSelling();
                s.push_back(M);
		tids[i] = M->sellerThread;
	}
	// create  L ticket sellers
	for(int i = 4; i < 10; i++) {
		Seller* L = new Seller(auditorium, "L" + std::to_string(i), N);
        L->StartSelling();
                s.push_back(L);
		tids[i] = L->sellerThread;
	}
    //Sleep to allow threads to create (segfaults sometime if not), then wake up at same time
    sleep(5);
    printf("\n~~All threads succesfully started~~\n\n");
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
	printf("%d customers not seated.\n", turned_away_customers);



	exit(0);
}
