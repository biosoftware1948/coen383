#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct Customer{
    int id; //customer id ex 101, 201, 102,
    char type; //type of buyer either H, M, L
} Customer;

Customer* createCustomers(int n, char type);

void printCustomers(Customer* c, int n);
#endif