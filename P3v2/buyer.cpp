#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#include "buyer.h"


//create new buyer
void createBuyer(Buyer *b, int id) {
	b->ID = id;
    //buyers arrive under 59 miniutes
	b->arrived = rand() % 60;
    //-1 so we know customer has no seat
	b->row_number = -1;
	b->column_number = -1;
}

void setBuyerSeat(Buyer* b, int r, int s) {
	b->row_number = r;
	b->column_number = s;
}

//OVerload this so its easy to compare who is next in priority queue
bool operator<(const Buyer& b, const Buyer& b2) {
	if(b.arrived > b2.arrived) {
		return true;
	}
	return false;
}
//OVerload this so its easy to compare who is next in priority queue
bool operator<=(const Buyer& b, const Buyer& b2) {
		if(b.arrived >= b2.arrived) {
		return true;
	}
	return false;
}
