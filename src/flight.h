#ifndef FLIGHT_H
#define FLIGHT_H

typedef struct {
    char flightNumber[10];
    char departure[30];
    char destination[30];
    char date[11];
    char time[6];
    char arrivalDate[11];  
    char arrivalTime[6];   
    int firstClassSeatsAvailable;
    int firstClassSeatsSold;
    int economySeatsAvailable; 
    int economySeatsSold;       
} Flight;

void createFlight();
void updateFlight(char* flightNumber);
void deleteFlight(char* flightNumber);
void displayFlights();

int isLeapYear(int year);
int isValidDate(char *date);
int isValidTime(char *time);

#endif