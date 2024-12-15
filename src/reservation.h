#ifndef RESERVATION_H
#define RESERVATION_H

#include "database.h"

typedef struct {
    char name[50];
    char email[50];
    char password[20];
    char seatNumber[3];
    char flightNumber[10];
} Reservation;

void makeReservation(Passenger passenger, Flight flight);
void cancelReservation(Passenger passenger, Flight flight);
void displayReservationDetails(Passenger passenger);

#endif