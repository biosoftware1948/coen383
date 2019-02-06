#include "seats.h"

Auditorium* createAuditorium() {
    Auditorium* a = (Auditorium*) malloc(sizeof(Auditorium));
    for(int i = 0; i < 10; ++i) {
        for(int j = 0; j < 10; ++j) {
            a->seats[i][j].type = '-';
            a->seats[i][j].customer_id = -1;
            a->seats[i][j].seller_id = -1;

        }
    }
    a->reserved_seats = 0;
    return a;
}

void deleteAuditorium(Auditorium* a) {
    free(a);
}

void printAuditorium(Auditorium* a) {
    for(int i = 0; i < 10; ++i) {
        for(int j = 0; j < 10; ++j) {
            if(a->seats[i][j].customer_id == -1){
                printf("|    -   |");
            }
            else {
                printf("|  %c%d%02d  |", a->seats[i][j].type, a->seats[i][j].seller_id, a->seats[i][j].customer_id);
            }
        
        }
        printf("\n");
    }
    printf("\n\n");
}

