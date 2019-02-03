#ifndef SEATS_H
#define SEATS_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct Seat {
    char type; // customer type
    int id; // customer id
} Seat;

typedef struct Auditorium {
    Seat seats[10][10];
} Auditorium;

Auditorium* createAuditorium();
void deleteAuditorium(Auditorium* a);

#endif