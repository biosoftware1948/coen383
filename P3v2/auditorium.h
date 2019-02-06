#ifndef AUDITORIUM_H
#define AUDITORIUM_H

#include <stdio.h>
#include <string>
#include "buyer.h"



// function to initialize the concert seats
//initialize_concert(std::string c[10][10]);

void createAuditorium(std::string s[10][10]);

// function to print the concert seating
void printAuditorium(std::string a[10][10]);

// function to print a customer purchasing a ticket and leaving
void printPurchase(Buyer* b, const char* s);
void printTime(int clock);

// function to print that the concert is soldout and the customer is turned away
void printSoldout(int clock_time, Buyer* b, const char* s);

#endif
