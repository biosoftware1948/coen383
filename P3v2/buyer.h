#ifndef BUYER_H
#define BUYER_H

//Buyer datastructure
typedef struct Buyer {
	int ID;
	int arrived;
	int row_number;
	int column_number;
	
	
} Buyer;

bool operator<(const Buyer& c, const Buyer& d);
bool operator<=(const Buyer& c, const Buyer& d);
//utils for create and update buyer
void createBuyer(Buyer *c, int id);
void setBuyerSeat(Buyer* c, int r, int s);



#endif