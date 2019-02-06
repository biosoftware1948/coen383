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
extern pthread_mutex_t print_lock;
extern volatile int clock_time;
extern int max_time;

// create a variable to tell when all the tickets have been sold
extern volatile int tickets_available;
extern pthread_mutex_t tickets_available_mutex;
extern volatile int rowH;
extern volatile int seatH;
extern volatile int rowM;
extern volatile int seatM;
extern volatile int rowL;
extern volatile int seatL;
extern pthread_mutex_t seating_index_mutex;
extern volatile int seated_customers_H;
extern volatile int seated_customers_M;
extern volatile int seated_customers_L;
extern volatile int turned_away_customers;

class Seller {
	private:
		// sellers customer queue
		std::priority_queue<Buyer> buyerQueue;
		// reference to customer seats
		std::string (*auditorium)[10];
		// reference to thread

		// remaining customer service time
		int service_time;

	public:
    pthread_t sellerThread;
    		// seller type
		std::string type;
		// constructor
		Seller(std::string auditorium[][10], std::string seller_type, int queue_size);

		void* sell();
		// remove a customer from the sellers queue
		int get_service_time();
		// get the current row for seating
		int get_row();
		// get the current seat to be used
		int get_seat();
		// set the next free seat
		void set_next_free_seat();
};
