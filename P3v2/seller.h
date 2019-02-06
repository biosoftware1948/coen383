#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <queue>
#include <iostream>
#include <pthread.h>

#include "buyer.h"
#include "auditorium.h"

extern pthread_cond_t cond_go;
extern pthread_mutex_t mutex_condition;
extern pthread_mutex_t mutex_sell;

extern volatile int clock_time;
extern int MAXIMUM_RUN_TIME;

// create a variable to tell when all the tickets have been sold
extern volatile int tickets_available;

extern volatile int H_CURRENT_ROW;
extern volatile int H_CURRENT_SEAT;
extern volatile int M_CURRENT_ROW;
extern volatile int M_CURRENT_SEAT;
extern volatile int L_CURRENT_ROW;
extern volatile int L_CURRENT_SEAT;
extern volatile int H_CUSTOMERS_WITH_SEATS;
extern volatile int M_CUSTOMERS_WITH_SEATS;
extern volatile int L_CUSTOMERS_WITH_SEATS;
extern volatile int turned_away_customers;


class Seller {
	private:
		std::priority_queue<Buyer> buyerQueue;
		// reference to auditorium
		std::string (*auditorium)[10];
		// remaining customer service time
		int service_time;

	public:
        pthread_t sellerThread;
		std::string type;         //H, M, or L
		Seller(std::string auditorium[][10], std::string type, int N);
		void* sell();
        //create new sell time depending on type H, M, L
		int sellerRandomSellTime();
		// get the current row for seating
		int currentRow();
		// get the current seat to be used
		int currentSeat();
		// gets seller to find new seat to go to
		void getNewSeat();
};