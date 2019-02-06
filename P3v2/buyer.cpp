#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#include "buyer.h"



bool operator<(const Buyer& b, const Buyer& b2) {
	if(b.arrival_time > b2.arrival_time) {
		return true;
	}
	return false;
}

bool operator<=(const Buyer& b, const Buyer& b2) {
		if(b.arrival_time >= b2.arrival_time) {
		return true;
	}
	return false;
}



//create new buyer
void createBuyer(Buyer *b, int id) {
	b->ID = id;
    //under 1 hour
	b->arrival_time = rand() % 60;
	// use -1 to represent the customer doesn't have a seat
	b->row_number = -1;
	b->column_number = -1;
}


// set Buyer seat
void setBuyerSeat(Buyer* b, int r, int s) {
	b->row_number = r;
	b->column_number = s;
}
