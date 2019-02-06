#ifndef BUYER_H
#define BUYER_H

//Buyer datastructure
typedef struct Buyer {
	int ID;
	int arrival_time;
	int row_number;
	int column_number;
	
	
} Buyer;

// overload the operators for the priority queues
//bool operator<(const Customer& c, const Customer& d);
//bool operator<=(const Customer& c, const Customer& d);

bool operator<(const Buyer& c, const Buyer& d);
bool operator<=(const Buyer& c, const Buyer& d);

// initialize the customer data
//void generate_customer(Customer *c, int id);
void createBuyer(Buyer *c, int id);

// set the customer's seat assignment
//void set_customer_seat(Customer* c, int r, int s);
void setBuyerSeat(Buyer* c, int r, int s);



#endif