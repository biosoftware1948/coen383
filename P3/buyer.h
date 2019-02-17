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
// function to print a customer purchasing a ticket and leaving
void printPurchase(Buyer* b, const char* s);
void printTime(int clock);
//print message if no tickets
void printSoldout(int clock_time, Buyer* b, const char* s);



#endif