#ifndef DATABASE_H
#define DATABASE_H

#include "flight.h"

#define MAX_FLIGHTS 100

typedef struct {
    char name[50];
} Passenger;

extern Flight flights[MAX_FLIGHTS];
extern int flightCount;

void loadFlights();
void saveFlights();

#endif