#include "seats.h"

Auditorium* createAuditorium() {
    Auditorium* a = (Auditorium*) malloc(sizeof(Auditorium));
    for(int i = 0; i < 10; ++i) {
        for(int j = 0; j < 10; ++j) {
            a->seats[i][j].type = '-';
            a->seats[i][j].id = -1;

        }
    }
    return a;
}

void deleteAuditorium(Auditorium* a) {
    free(a);
}