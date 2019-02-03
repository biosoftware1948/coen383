#include "queue.h"
#include "seller.h"

Seller* createSeller(char type, int id, int num_customers, Auditorium* a) {
    //build structure
    Seller* s = (Seller*) malloc(sizeof(Seller));
    s->type = type;
    s->id = id;
    s->customerQueue = createQueue();
    s->auditorium = a;
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