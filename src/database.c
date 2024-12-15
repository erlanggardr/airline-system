#include <stdio.h>
#include "database.h"

void loadFlights() {
    FILE* file = fopen("data/flights.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open flights data file for reading.\n");
        flightCount = 0;
        return;
    }
    
    flightCount = 0;
    while (fscanf(file, "%9s %29s %29s %10s %5s %10s %5s %d %d %d %d",
                  flights[flightCount].flightNumber,
                  flights[flightCount].departure,
                  flights[flightCount].destination,
                  flights[flightCount].date,
                  flights[flightCount].time,
                  flights[flightCount].arrivalDate,
                  flights[flightCount].arrivalTime,
                  &flights[flightCount].firstClassSeatsAvailable,
                  &flights[flightCount].firstClassSeatsSold,
                  &flights[flightCount].economySeatsAvailable,
                  &flights[flightCount].economySeatsSold) == 11) {
        flightCount++;
    }
    fclose(file);
}

void saveFlights() {
    FILE* file = fopen("data/flights.txt", "w");
    if (file == NULL) {
        printf("Error: Could not open flights data file for writing.\n");
        return;
    }
    
    for (int i = 0; i < flightCount; i++) {
        fprintf(file, "%s %s %s %s %s %s %s %d %d %d %d\n",
                flights[i].flightNumber,
                flights[i].departure,
                flights[i].destination,
                flights[i].date,
                flights[i].time,
                flights[i].arrivalDate,
                flights[i].arrivalTime,
                flights[i].firstClassSeatsAvailable,
                flights[i].firstClassSeatsSold,
                flights[i].economySeatsAvailable,
                flights[i].economySeatsSold);
    }
    fclose(file);
}