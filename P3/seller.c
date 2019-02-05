#include "queue.h"
#include "seller.h"

Seller* createSeller(char type, int id, int starting_row,int num_customers, Auditorium* a) {
    //build structure
    Seller* s = (Seller*) malloc(sizeof(Seller));
    s->type = type;
    s->id = id;
    s->customerQueue = createQueue();
    s->auditorium = a;
    s->current_row = starting_row;
    //populate queue
    Customer* c = createCustomers(num_customers, type);
    for(int i = 0; i < num_customers; ++i) {
        enQueue(s->customerQueue, &c[i]);
    }

    return s;
}
void deleteSeller(Seller* s) {
    removeContents(s->customerQueue);
    free(s->customerQueue);
    free(s);
}

void printSellerCustomers(Seller* s) {
    printQueue(s->customerQueue);
}

// function to get random service time
int get_service_time(Seller* seller) {
	// for H: 1-2 minutes
	if(seller->type == 'H') {
		return ((rand() % 2) + 1);
	}
	// for M: 2, 3, or 4 minutes
	else if(seller->type == 'M') {
		return ((rand() % 3) + 2);
	}
	// for L: 4, 5, 6, or 7 minutes
	else if(seller->type == 'L') {
		return ((rand() % 4) + 4);
	}
}

void reserveSeat(Seller* seller, int column) {
    Customer* c = deQueue(seller->customerQueue);
    seller->auditorium->seats[seller->current_row][column].customer_id = c->id;
    seller->auditorium->seats[seller->current_row][column].seller_id = seller->id;
    seller->auditorium->seats[seller->current_row][column].type= c->type;
}

int getNewMRow(int current_row) {
    if (current_row == 5) {
        return 6;
    }
     if (current_row == 6) {
         return 4;
    }
    if (current_row == 4) {
        return 7;
    }
    if (current_row == 7) {
        return 3;
    }
    if (current_row == 3) {
        return 8;
    }
    if (current_row == 8) {
        return 2;
    }
    if (current_row == 2) {
        return 9;
    }
    if (current_row == 9) {
        return 1;
    }
    if (current_row == 1) {
        return 10;
    }
}

