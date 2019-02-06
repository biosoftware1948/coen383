#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <queue>
#include <iostream>
#include <pthread.h>
#include <vector>
#include <unistd.h>

#include "buyer.h"
#include "auditorium.h"

extern pthread_cond_t cond_go;
extern pthread_mutex_t mutex_condition;
extern pthread_mutex_t selling_mutex;
extern pthread_mutex_t std_output;

extern volatile int timer;
extern int MAXIMUM_RUN_TIME;

// create a variable to tell when all the tickets have been sold
extern volatile int tickets_for_sale;

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
		std::vector<Buyer> allBuyers;
		// reference to auditorium
		std::string (*auditorium)[10];
		// remaining customer service time
		int service_time;
        int id;
        int seats;

		class Transaction {
		public:
			Buyer _b;
			int time;
			int row;
			int col;
			Transaction(Buyer a, int b, int c, int d) {
				_b = a;
				time = b;
				row = c;
				col = d;
			}
		};

		std::vector<Transaction> transactions;
		void printStarted(Transaction t);
		void finishSale(Transaction t);

	public:
        pthread_t sellerThread;
		std::string type;         //H, M, or L
		Seller(std::string auditorium[10][10], std::string type, int N);
		void* sell();
        //create new sell time depending on type H, M, L
		int sellerRandomSellTime();
		// get the current row for seating
		int currentRow();
		// get the current seat to be used
		int currentColumn();
		// gets seller to find new seat to go to
		void getNewSeat();
        void StartSelling();
        void increaseBuyerCount();
        bool checkIfDone();
        void printAvailables(int);
        void printAllBuyers();
};
