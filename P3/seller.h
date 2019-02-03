#ifndef SELLER_H
#define SELLER_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


#include "queue.h"
#include "seats.h"

typedef struct Seller {
    Queue* customerQueue;
    int id; //ids 0-9 for the 10 sellers
    char type; // H, M, L sellers
    Auditorium* auditorium;
} Seller;

Seller* createSeller(char type, int id, int num_customers, Auditorium* a);
void deleteSeller(Seller* s);
void printSellerCustomers(Seller* s);





#endif