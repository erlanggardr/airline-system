#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reservation.h"
#include "database.h"

void makeReservation(Passenger passenger, Flight flight) {
    for (int i = 0; i < flightCount; i++) {
        if (strcmp(flights[i].flightNumber, flight.flightNumber) == 0) {
            if (flights[i].firstClassSeatsAvailable > 0 || 
                flights[i].economySeatsAvailable > 0) {
                
                char seatClass;
                printf("Choose seat class (F for First Class, E for Economy): ");
                scanf(" %c", &seatClass);

                if (seatClass == 'F' || seatClass == 'f') {
                    if (flights[i].firstClassSeatsAvailable > 0) {
                        flights[i].firstClassSeatsAvailable--;
                        flights[i].firstClassSeatsSold++;
                        printf("First class seat booked successfully!\n");
                    } else {
                        printf("No first class seats available.\n");
                        return;
                    }
                } else if (seatClass == 'E' || seatClass == 'e') {
                    if (flights[i].economySeatsAvailable > 0) {
                        flights[i].economySeatsAvailable--;
                        flights[i].economySeatsSold++;
                        printf("Economy seat booked successfully!\n");
                    } else {
                        printf("No economy seats available.\n");
                        return;
                    }
                } else {
                    printf("Invalid seat class!\n");
                    return;
                }

                FILE *file = fopen("data/reservations.txt", "a");
                if (file == NULL) {
                    printf("Error: Could not open or create reservations file for appending.\n");
                    return;
                }
                if (fprintf(file, "%s,%s,%c\n", passenger.name, flight.flightNumber, seatClass) < 0) {
                    printf("Error: Failed to write reservation to file.\n");
                }
                fclose(file);
                
                printf("Reservation made for %s on flight %s.\n", passenger.name, flight.flightNumber);
                return;
            } else {
                printf("Sorry, flight is fully booked!\n");
                return;
            }
        }
    }
    printf("Flight not found!\n");
}

void cancelReservation(Passenger passenger, Flight flight) {
    FILE *file = fopen("data/reservations.txt", "r");
    if (file == NULL) {
        printf("No reservations found to cancel.\n");
        return;
    }
    FILE *temp = fopen("data/temp.txt", "w");
    if (temp == NULL) {
        printf("Error: Could not open temporary file for writing.\n");
        fclose(file);
        return;
    }

    int found = 0;
    char name[50], flightNum[10], seatClass;

    while (fscanf(file, "%49[^,],%9[^,],%c\n", name, flightNum, &seatClass) != EOF) {
        if (strcmp(name, passenger.name) == 0 && strcmp(flightNum, flight.flightNumber) == 0) {
            found = 1;
            for (int i = 0; i < flightCount; i++) {
                if (strcmp(flights[i].flightNumber, flightNum) == 0) {
                    if (seatClass == 'F' || seatClass == 'f') {
                        flights[i].firstClassSeatsAvailable++;
                        flights[i].firstClassSeatsSold--;
                    } else if (seatClass == 'E' || seatClass == 'e') {
                        flights[i].economySeatsAvailable++;
                        flights[i].economySeatsSold--;
                    }
                    break;
                }
            }
        } else {
            fprintf(temp, "%s,%s,%c\n", name, flightNum, seatClass);
        }
    }

    fclose(file);
    fclose(temp);

    if (found) {
        remove("data/reservations.txt");
        rename("data/temp.txt", "data/reservations.txt");
        printf("Reservation cancelled successfully!\n");
    } else {
        remove("data/temp.txt");
        printf("Reservation not found!\n");
    }
}

void displayReservationDetails(Passenger passenger) {
    FILE *file = fopen("data/reservations.txt", "r");
    if (file == NULL) {
        printf("No reservations found for %s.\n", passenger.name);
        return;
    }

    char name[50], flightNum[10], seatClass;
    int found = 0;

    printf("\nReservations for %s:\n", passenger.name);
    printf("%-15s %-10s %-10s\n", "Flight", "Class", "Status");
    printf("--------------------------------\n");

    while (fscanf(file, "%49[^,],%9[^,],%c\n", name, flightNum, &seatClass) != EOF) {
        if (strcmp(name, passenger.name) == 0) {
            printf("%-15s %-10c Confirmed\n", flightNum, seatClass);
            found = 1;
        }
    }

    if (!found) {
        printf("No reservations found for this passenger.\n");
    }

    fclose(file);
}