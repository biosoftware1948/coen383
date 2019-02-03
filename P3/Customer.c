#include "Customer.h"

Customer* createCustomers(int n, char type) {
    Customer* custArray = (Customer*) malloc(sizeof(Customer) * n);
    for(int i = 0; i < n; ++i) {
        custArray[i].type = type;
        custArray[i].id = i;
    }
    return custArray;
}

void printCustomers(Customer* c, int n) {
    for(int i = 0; i < n; ++i) {
        printf("Customer: %c%03d\n", c[i].type, c[i].id);
    }
}