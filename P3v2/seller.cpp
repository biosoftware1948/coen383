#include "seller.h"


static void* sell_x(void* object) {
	return ((Seller*) object)->sell();
}

// 3 argument constructor
Seller::Seller(std::string seats[][10], std::string seller_type, int queue_size) {
	this->auditorium = seats;
	this->type = seller_type;
	this->service_time = 0;
	// call function to populate the customer queue
    for(int i = 0; i < queue_size; i++) {
		Buyer b;
		createBuyer(&b, i);
		this->buyerQueue.push(b);
	}


	// pass pthread_create "this" to call a member function in sell_x
	pthread_create(&this->sellerThread, NULL, sell_x, (void*) this);
}


void* Seller::sell() {
	pthread_mutex_lock(&mutex_condition);
	pthread_cond_wait(&cond_go, &mutex_condition);
	pthread_mutex_unlock(&mutex_condition);
	while(clock_time < max_time) {
		int ready_for_customer = 0;
		// check if it is time to serve the next customer and that the queue is not empty
		if((clock_time >= buyerQueue.top().arrival_time) && (!this->buyerQueue.empty()) && (clock_time >= ready_for_customer)) {
				
			// get the customer from the queue
			Buyer b = this->buyerQueue.top();
			// pop the customer from the queue
			this->buyerQueue.pop();
			// get the random service time required for the customer
			int serve_time = get_service_time();
			

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
					avail_row = get_row();
					// get the available seat
					avail_seat = get_seat();
					// set the next available seat if there are still tickets available
					set_next_free_seat();
					// put in an exit condition for the threads to prevent infinite loop looking for seat
					if(('H' == this->type[0]) && (9 < rowH)) {
						break;
					}
					else if(('M' == this->type[0]) && (0 > rowM)) {
						break;
					}
					else if(('L' == this->type[0]) && (0 > rowL)) {
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
					seated_customers_H++;
				}
				else if('M' == this->type[0]) {
					seated_customers_M++;
				}
				else if('L' == this->type[0]) {
					seated_customers_L++;
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
int Seller::get_service_time() {
	// for H: 1-2 minutes
	if('H' == this->type[0]) {
		return ((rand() % 2) + 1);
	}
	// for M: 2, 3, or 4 minutes
	else if('M' == this->type[0]) {
		return ((rand() % 3) + 2);
	}
	// for L: 4, 5, 6, or 7 minutes
	else if('L' == this->type[0]) {
		return ((rand() % 4) + 4);
	}
}

// function that sets the next free seat
// requires getting the lock prior to its call
void Seller::set_next_free_seat() {
	// check if this is a H ticket seller
	if('H' == this->type[0]) {
		// increment the seat
		seatH++;
		// check if the seat and row need to be adjusted
		if(9 < seatH) {
			seatH = 0;
			rowH++;
		}
	}
	// check if this is a M ticket seller
	else if('M' == this->type[0]) {
		// increment the seat
		seatM++;
		// check if the seat and row need to be adjusted
		if(9 < seatM) {
			seatM = 0;
			// determine which row to begin assigning next
			if(5 == rowM) {
				rowM = 6;
			}
			else if(6 == rowM) {
				rowM = 4;
			}
			else if(4 == rowM) {
				rowM = 7;
			}
			else if(7 == rowM) {
				rowM = 3;
			}
			else if(3 == rowM) {
				rowM = 8;
			}
			else if(8 == rowM) {
				rowM = 2;
			}
			else if(2 == rowM) {
				rowM = 9;
			}
			else if(9 == rowM) {
				rowM = 1;
			}
			else if(1 == rowM) {
				rowM = 0;
			}
			else if(0 == rowM) {
				rowM = -1;
			}
		}
	}
	// check if this is a L ticket seller
	else if('L' == this->type[0]) {
		// increment the seat
		seatL++;
		// check if the seat and row need to be adjusted
		if(9 < seatL) {
			seatL = 0;
			rowL--;
		}
	}
}

// get the current row for seating
// requires getting the lock prior to its call
int Seller::get_row() {
	int r;
	// look at which row index to get
	if('H' == this->type[0]) {
		r = rowH;
	}
	else if('M' == this->type[0]) {
		r = rowM;
	}
	else if('L' == this->type[0]) {
		r = rowL;
	}
	// return the row index
	return r;
}

// get the current seat to be used
// requires getting the lock prior to its call
int Seller::get_seat() {
	int s;
	// look at which seat index to get
	if('H' == this->type[0]) {
		s = seatH;
	}
	else if('M' == this->type[0]) {
		s = seatM;
	}
	else if('L' == this->type[0]) {
		s = seatL;
	}
	// return the seat index
	return s;
}


