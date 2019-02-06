#ifndef AUDITORIUM_H
#define AUDITORIUM_H

#include <stdio.h>
#include <string>
#include "buyer.h"

void createAuditorium(std::string s[10][10]);

// function to print the auditorium
void printAuditorium(std::string a[10][10]);

// function to print a customer purchasing a ticket and leaving
void printPurchase(Buyer* b, const char* s);
void printTime(int clock);

void printSoldout(int clock_time, Buyer* b, const char* s);

#endif
