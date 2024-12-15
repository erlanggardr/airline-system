#include <stdio.h>
#include <string.h>
#include "flight.h"
#include "database.h"

int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int isValidDate(char *date) {
    int day, month, year;
    
    if (sscanf(date, "%d/%d/%d", &day, &month, &year) != 3) {
        printf("Error: Invalid date format! Please use DD/MM/YYYY\n");
        return 0;
    }
    
    if (day == 0 && month == 0 && year == 0) {
        printf("Error: Date cannot be all zeros!\n");
        return 0;
    }
    if (day == 0) {
        printf("Error: Day cannot be zero!\n");
        return 0;
    }
    if (month == 0) {
        printf("Error: Month cannot be zero!\n");
        return 0;
    }
    if (year == 0) {
        printf("Error: Year cannot be zero!\n");
        return 0;
    }
    
    if (month < 1 || month > 12) {
        printf("Error: Month must be between 1 and 12!\n");
        return 0;
    }

    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if (isLeapYear(year)) {
        daysInMonth[1] = 29;
    }

    if (day < 1 || day > daysInMonth[month - 1]) {
        if (month == 2) {
            if (isLeapYear(year)) {
                printf("Error: February in %d (leap year) can only have up to 29 days!\n", year);
            } else {
                printf("Error: February in %d (non-leap year) can only have up to 28 days!\n", year);
            }
        } else {
            printf("Error: Month %d can only have up to %d days!\n", 
                   month, daysInMonth[month - 1]);
        }
        return 0;
    }

    return 1;
}

int isValidTime(char *time) {
    int hour, minute;
    
    if (sscanf(time, "%d:%d", &hour, &minute) != 2) {
        printf("Error: Invalid time format! Please use HH:MM (e.g., 13:30)\n");
        return 0;
    }

    if (hour < 0 || hour > 23) {
        printf("Error: Hour must be between 00 and 23!\n");
        return 0;
    }
    
    if (minute < 0 || minute > 59) {
        printf("Error: Minutes must be between 00 and 59!\n");
        return 0;
    }

    return 1;
}

Flight flights[MAX_FLIGHTS];
int flightCount = 0;

void createFlight() {
    if (flightCount >= MAX_FLIGHTS) {
        printf("Maximum flights reached!\n");
        return;
    }

    Flight f;
    int isDuplicate;
    do {
        isDuplicate = 0;
        printf("Enter flight number: ");
        scanf("%9s", f.flightNumber);
        for (int i = 0; i < flightCount; i++) {
            if (strcmp(flights[i].flightNumber, f.flightNumber) == 0) {
                printf("Flight number already exists! Please enter a unique flight number.\n");
                isDuplicate = 1;
                break;
            }
        }
    } while (isDuplicate);

    printf("Enter departure city: ");
    scanf("%29s", f.departure);

    printf("Enter destination: ");
    scanf("%29s", f.destination);

    do {
        printf("Enter date (DD/MM/YYYY): ");
        scanf("%s", f.date);
        if (!isValidDate(f.date)) {
            printf("Invalid date! Please check:\n");
            printf("- Day should be valid for the month\n");
            printf("- Month should be between 1-12\n");
            printf("- February should have 29 days in leap years\n");
            printf("- Date cannot be all zeros\n");
        }
    } while (!isValidDate(f.date));

    do {
        printf("Enter time (HH:MM): ");
        scanf("%s", f.time);
        if (!isValidTime(f.time)) {
            printf("Invalid time! Format should be HH:MM (00:00 - 23:59)\n");
        }
    } while (!isValidTime(f.time));

    do {
        printf("Enter arrival date (DD/MM/YYYY): ");
        scanf("%s", f.arrivalDate);
        if (!isValidDate(f.arrivalDate)) {
            printf("Invalid arrival date!\n");
        }
    } while (!isValidDate(f.arrivalDate));

    do {
        printf("Enter arrival time (HH:MM): ");
        scanf("%s", f.arrivalTime);
        if (!isValidTime(f.arrivalTime)) {
            printf("Invalid arrival time!\n");
        }
    } while (!isValidTime(f.arrivalTime));

    do {
        printf("Enter number of first class seats available: ");
        if (scanf("%d", &f.firstClassSeatsAvailable) != 1 || f.firstClassSeatsAvailable < 0) {
            printf("Invalid input! Number of first class seats available must be a non-negative integer.\n");
            while (getchar() != '\n');
            f.firstClassSeatsAvailable = -1;
        }
    } while (f.firstClassSeatsAvailable < 0);

    f.firstClassSeatsSold = 0;

    do {
        printf("Enter number of economy seats available: ");
        if (scanf("%d", &f.economySeatsAvailable) != 1 || f.economySeatsAvailable < 0) {
            printf("Invalid input! Number of economy seats available must be a non-negative integer.\n");
            while (getchar() != '\n');
            f.economySeatsAvailable = -1;
        }
    } while (f.economySeatsAvailable < 0);

    f.economySeatsSold = 0;

    flights[flightCount++] = f;
    printf("Flight created successfully!\n");
}

void updateFlight(char* flightNumber) {
    for (int i = 0; i < flightCount; i++) {
        if (strcmp(flights[i].flightNumber, flightNumber) == 0) {
            printf("\nUpdating Flight %s\n", flightNumber);
            printf("Enter new departure city: ");
            scanf("%29s", flights[i].departure);
            
            printf("Enter new destination: ");
            scanf("%29s", flights[i].destination);
            
            do {
                printf("Enter new departure date (DD/MM/YYYY): ");
                scanf("%s", flights[i].date);
                if (!isValidDate(flights[i].date)) {
                    printf("Invalid departure date! Please try again.\n");
                }
            } while (!isValidDate(flights[i].date));

            do {
                printf("Enter new departure time (HH:MM): ");
                scanf("%s", flights[i].time);
                if (!isValidTime(flights[i].time)) {
                    printf("Invalid departure time! Please try again.\n");
                }
            } while (!isValidTime(flights[i].time));

            do {
                printf("Enter new arrival date (DD/MM/YYYY): ");
                scanf("%s", flights[i].arrivalDate);
                if (!isValidDate(flights[i].arrivalDate)) {
                    printf("Invalid arrival date! Please try again.\n");
                }
            } while (!isValidDate(flights[i].arrivalDate));

            do {
                printf("Enter new arrival time (HH:MM): ");
                scanf("%s", flights[i].arrivalTime);
                if (!isValidTime(flights[i].arrivalTime)) {
                    printf("Invalid arrival time! Please try again.\n");
                }
            } while (!isValidTime(flights[i].arrivalTime));

            do {
                printf("Enter new number of first class seats available: ");
                if (scanf("%d", &flights[i].firstClassSeatsAvailable) != 1 || flights[i].firstClassSeatsAvailable < 0) {
                    printf("Invalid input! Number of first class seats available must be a non-negative integer.\n");
                    while (getchar() != '\n');
                    flights[i].firstClassSeatsAvailable = -1;
                }
            } while (flights[i].firstClassSeatsAvailable < 0);

            do {
                printf("Enter new number of economy seats available: ");
                if (scanf("%d", &flights[i].economySeatsAvailable) != 1 || flights[i].economySeatsAvailable < 0) {
                    printf("Invalid input! Number of economy seats available must be a non-negative integer.\n");
                    while (getchar() != '\n');
                    flights[i].economySeatsAvailable = -1;
                }
            } while (flights[i].economySeatsAvailable < 0);

            printf("\nFlight updated successfully!\n");
            return;
        }
    }
    printf("Flight not found!\n");
}

void deleteFlight(char* flightNumber) {
    int found = 0;
    for (int i = 0; i < flightCount; i++) {
        if (strcmp(flights[i].flightNumber, flightNumber) == 0) {
            for (int j = i; j < flightCount - 1; j++) {
                flights[j] = flights[j + 1];
            }
            flightCount--;
            found = 1;
            printf("Flight deleted successfully!\n");
            break;
        }
    }
    if (!found) {
        printf("Flight not found!\n");
        return;
    }

    FILE *file = fopen("data/reservations.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open reservations file for reading.\n");
        return;
    }
    FILE *temp = fopen("data/temp_reservations.txt", "w");
    if (temp == NULL) {
        printf("Error: Could not open temporary file for writing.\n");
        fclose(file);
        return;
    }

    char line[200];
    char name[50], flightNum[10], seatClass;
    int reservationsRemoved = 0;

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%[^,],%[^,],%c", name, flightNum, &seatClass) == 3) {
            if (strcmp(flightNum, flightNumber) != 0) {
                fprintf(temp, "%s", line);
            } else {
                reservationsRemoved++;
            }
        }
    }

    fclose(file);
    fclose(temp);

    if (remove("data/reservations.txt") != 0) {
        printf("Error: Could not remove the original reservations file.\n");
        return;
    }
    if (rename("data/temp_reservations.txt", "data/reservations.txt") != 0) {
        printf("Error: Could not rename the temporary reservations file.\n");
        return;
    }

    if (reservationsRemoved > 0) {
        printf("%d reservation(s) associated with flight %s have been removed.\n", reservationsRemoved, flightNumber);
    }
}

void displayFlights() {
    if (flightCount == 0) {
        printf("No flights available!\n");
        return;
    }
    
    printf("\nFlight List:\n");
    printf("%-10s %-15s %-15s %-12s %-8s %-12s %-8s %-6s %-6s\n", 
           "Flight#", "From", "To", "Dept Date", "Time", "Arrv Date", "Time", "F/Avl", "E/Avl");
    printf("---------------------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < flightCount; i++) {
        int firstAvail = flights[i].firstClassSeatsAvailable;
        int economyAvail = flights[i].economySeatsAvailable;

        printf("%-10s %-15s %-15s %-12s %-8s %-12s %-8s %-6d %-6d\n",
               flights[i].flightNumber,
               flights[i].departure,
               flights[i].destination,
               flights[i].date,
               flights[i].time,
               flights[i].arrivalDate,
               flights[i].arrivalTime,
               firstAvail,
               economyAvail);
    }
    printf("\nLegend: F/Avl = First Class Available, E/Avl = Economy Available\n");
}
