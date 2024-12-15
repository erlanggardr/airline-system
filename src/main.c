#include <stdio.h>
#include <string.h>
#include "flight.h"
#include "database.h"
#include "reservation.h"

void displayMenu() {
    printf("\n=== Airline Reservation System ===\n");
    printf("1. Create Flight\n");
    printf("2. Update Flight\n");
    printf("3. Delete Flight\n");
    printf("4. Display Flights\n");
    printf("5. Make Reservation\n");
    printf("6. Cancel Reservation\n");
    printf("7. View Reservation Details\n");
    printf("8. Exit\n");
    printf("Choose an option: ");
}

int main() {
    int choice;
    loadFlights();

    do {
        displayMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number between 1 and 8.\n");
            while (getchar() != '\n');
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1:
                createFlight();
                break;
            case 2: {
                char flightNum[10];
                printf("Enter flight number: ");
                scanf("%9s", flightNum);
                updateFlight(flightNum);
                break;
            }
            case 3: {
                char flightNum[10];
                printf("Enter flight number: ");
                scanf("%9s", flightNum);
                deleteFlight(flightNum);
                break;
            }
            case 4:
                displayFlights();
                break;
            case 5: {
                Passenger passenger;
                Flight flight;
                printf("Enter passenger name: ");
                getchar(); 
                fgets(passenger.name, sizeof(passenger.name), stdin);
                passenger.name[strcspn(passenger.name, "\n")] = '\0'; 
                printf("Enter flight number: ");
                scanf("%9s", flight.flightNumber);
                makeReservation(passenger, flight);
                break;
            }
            case 6: {
                Passenger passenger;
                Flight flight;
                printf("Enter passenger name: ");
                getchar(); 
                fgets(passenger.name, sizeof(passenger.name), stdin);
                passenger.name[strcspn(passenger.name, "\n")] = '\0'; 
                printf("Enter flight number: ");
                scanf("%9s", flight.flightNumber);
                cancelReservation(passenger, flight);
                break;
            }
            case 7: {
                Passenger passenger;
                printf("Enter passenger name: ");
                getchar(); 
                fgets(passenger.name, sizeof(passenger.name), stdin);
                passenger.name[strcspn(passenger.name, "\n")] = '\0'; 
                displayReservationDetails(passenger);
                break;
            }
            case 8:
                printf("Saving and exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 8);

    saveFlights();
    return 0;
}