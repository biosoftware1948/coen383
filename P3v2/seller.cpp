#include "seller.h"

static void* startSales(void* seller) {
    return ((Seller*) seller)->sell();
}

Seller::Seller(std::string auditorium[][10], std::string type, int N) {
	this->auditorium = auditorium;
	this->type = type;
	this->service_time = 0;
	// call function to populate the customer queue
	for(int i = 0; i < N; i++) {
		Buyer b;
		createBuyer(&b, i);
		this->buyerQueue.push(b);
	}

	// pass pthread_create "this" to call a member function in sell_x
	pthread_create(&this->sellerThread, NULL, startSales, (void*) this);
}


void* Seller::sell() {
	pthread_mutex_lock(&mutex_condition);
	pthread_cond_wait(&cond_go, &mutex_condition);
	pthread_mutex_unlock(&mutex_condition);
	while(clock_time < MAXIMUM_RUN_TIME) {
		int ready_for_customer = 0;
		// check if it is time to serve the next customer and that the queue is not empty
		if((clock_time >= buyerQueue.top().arrival_time) && (!this->buyerQueue.empty()) && (clock_time >= ready_for_customer)) {
				
			// get the customer from the queue
			Buyer b = this->buyerQueue.top();
			// pop the customer from the queue
			this->buyerQueue.pop();
			// get the random service time required for the customer
			int serve_time = sellerRandomSellTime();
			

			pthread_mutex_lock(&mutex_sell);
			if(0 < tickets_available) {
				// customer is being serviced so set next available time
				ready_for_customer = (clock_time + serve_time);
				// decrement the number of remaining tickets
				tickets_available--;
				// variables to hold the row and seat indices
				int avail_row;
				int avail_seat;
				// get the next available seat and make sure it isn't already taken
				do {
					// get the available row
					avail_row = currentRow();
					// get the available seat
					avail_seat = currentSeat();
					// set the next available seat if there are still tickets available
					getNewSeat();
					// put in an exit condition for the threads to prevent infinite loop looking for seat
					if(('H' == this->type[0]) && (9 < H_CURRENT_ROW)) {
						break;
					}
					else if(('M' == this->type[0]) && (0 > M_CURRENT_ROW)) {
						break;
					}
					else if(('L' == this->type[0]) && (0 > L_CURRENT_ROW)) {
						break;
					}
					
					
				} while ("-" != this->auditorium[avail_row][avail_seat]);
				
				// print the purchase
                printTime(clock_time);
                //printf('\n');
				printPurchase(&b, this->type.c_str());
				// place the customer in the seat
				this->auditorium[avail_row][avail_seat] = (this->type + "0" + std::to_string(b.ID));
				// print the seating chart
				printAuditorium(this->auditorium);
				// create a space for the output
				printf("\n");
				// increment the number of customers that got seats
				if('H' == this->type[0]) {
					H_CUSTOMERS_WITH_SEATS++;
				}
				else if('M' == this->type[0]) {
					M_CUSTOMERS_WITH_SEATS++;
				}
				else if('L' == this->type[0]) {
					L_CUSTOMERS_WITH_SEATS++;
				}
			}
			else {
                printTime(clock_time);
                printf("\n");
				printSoldout(clock_time, &b, this->type.c_str());
				// increment the number of customers turned away
				turned_away_customers++;
			}
            //release mutex
			pthread_mutex_unlock(&mutex_sell);
		}
	}
	return NULL;
}


// function to get random service time
int Seller::sellerRandomSellTime() {
	// for H: 1-2 minutes
	if(this->type[0] == 'H') {
		return ((rand() % 2) + 1);
	}
	// for M: 2, 3, or 4 minutes
	else if(this->type[0] == 'M') {
		return ((rand() % 3) + 2);
	}
	// for L: 4, 5, 6, or 7 minutes
	else if(this->type[0] == 'L') {
		return ((rand() % 4) + 4);
	}
}

// function that sets the next free seat
// requires getting the lock prior to its call
void Seller::getNewSeat() {
	// check if this is a H ticket seller
	if('H' == this->type[0]) {
		// increment the seat
		H_CURRENT_SEAT++;
		//reset if hit the end
		if(H_CURRENT_SEAT > 9) {
			H_CURRENT_SEAT = 0;
			H_CURRENT_ROW++;
		}
	}
	// check if this is a M ticket seller
	else if('M' == this->type[0]) {
		// increment the seat
		M_CURRENT_SEAT++;
		// check if the seat and row need to be adjusted
		if(9 < M_CURRENT_SEAT) {
			M_CURRENT_SEAT = 0;
			// determine which row to begin assigning next
			if(5 == M_CURRENT_ROW) {
				M_CURRENT_ROW = 6;
			}
			else if(6 == M_CURRENT_ROW) {
				M_CURRENT_ROW = 4;
			}
			else if(4 == M_CURRENT_ROW) {
				M_CURRENT_ROW = 7;
			}
			else if(7 == M_CURRENT_ROW) {
				M_CURRENT_ROW = 3;
			}
			else if(3 == M_CURRENT_ROW) {
				M_CURRENT_ROW = 8;
			}
			else if(8 == M_CURRENT_ROW) {
				M_CURRENT_ROW = 2;
			}
			else if(2 == M_CURRENT_ROW) {
				M_CURRENT_ROW = 9;
			}
			else if(9 == M_CURRENT_ROW) {
				M_CURRENT_ROW = 1;
			}
			else if(1 == M_CURRENT_ROW) {
				M_CURRENT_ROW = 0;
			}
			else if(0 == M_CURRENT_ROW) {
				M_CURRENT_ROW = -1;
			}
		}
	}
	// check if this is a L ticket seller
	else if('L' == this->type[0]) {
		// increment the seat
		L_CURRENT_SEAT++;
		// check if the seat and row need to be adjusted
		if(9 < L_CURRENT_SEAT) {
			L_CURRENT_SEAT = 0;
			L_CURRENT_ROW--;
		}
	}
}

// get the current row for seating
// requires getting the lock prior to its call
int Seller::currentRow() {
	int r;
	// look at which row index to get
	if('H' == this->type[0]) {
		r = H_CURRENT_ROW;
	}
	else if('M' == this->type[0]) {
		r = M_CURRENT_ROW;
	}
	else if('L' == this->type[0]) {
		r = L_CURRENT_ROW;
	}
	// return the row index
	return r;
}

// get the current seat to be used
// requires getting the lock prior to its call
int Seller::currentSeat() {
	int s;
	// look at which seat index to get
	if('H' == this->type[0]) {
		s = H_CURRENT_SEAT;
	}
	else if('M' == this->type[0]) {
		s = M_CURRENT_SEAT;
	}
	else if('L' == this->type[0]) {
		s = L_CURRENT_SEAT;
	}
	// return the seat index
	return s;
}

