#include <stdio.h>
#include <conio.h>  // for getch()
#include <string.h>
#include "donguinesArrows.h"

// Asks for trip number and displays the seat map and passenger count for the trip.
// @param trip[]           array containing trip information (trip number, etc.)
// @param passengers[][]   array where the passenger information is stored
void
viewPassengerCount(struct TripInfo trip[],
                   struct Card passengers[][MAX_PASS])  
{
    stringTrip tripNo;

    int tripIndex = -1;

    int passengerCount = 0;
    char seatStatus[MAX_PASS];

    int i, j;

    do
    {
        // Ask user for trip number
        printPassengerCountTitle();
        
        displayTrips(trip);
        
        printf("Please enter the trip number (AE1xx): ");
        scanf("%5s", tripNo);

        // Check if trip number is valid
        tripIndex = isValidTrip(trip, tripNo);

        if(tripIndex == -1)
        {
            cls();
            printf("\033[0;31mERROR:\033[0m Trip not found or invalid. Please try again.\n\n");
        }
    }
    while(tripIndex == -1);

    // Count total passengers in trip
    // Assign X for taken seats and O for empty seats 
    for(i = 0; i < MAX_PASS; i++)
    {
        if(passengers[tripIndex][i].priorityNo != 99)
        {
            seatStatus[i] = 'X';
            passengerCount++;
        }
        else
        {
            seatStatus[i] = 'O';
        }
    }

    // Display seat map
    cls();
    printPassengerCountTitle();
    printf("Seat Map for Trip %s\n\n", trip[tripIndex].tripNumber);
    
    for(i = 0; i < 9; i++)
    {
        if(i % 2)
        {
            for(j = 0; j < 3; j++)
            {
                printf("| %c ", seatStatus[(i / 2 * 3) + j]);
            }
            printf("|");
        }
        else
        {
            printf("+---+---+---+");
        }

        printf("\n");
    }
    printf("| %c |       |\n", seatStatus[12]);
    printf("+---+---+---+\n\n");

    printf("Seats taken:     %d\n", passengerCount);
    printf("Seats available: %d\n\n", MAX_PASS - passengerCount);

    pressAnyKey();

    cls();
}

// Asks for trip number and displays drop-off points for the trip with corresponding passenger counts
// @param trip[]           array containing trip information (trip number, etc.)
// @param passengers[][]   array where the passenger information is stored
// @param dropOffs[][]     array containing full names of drop-off points
void
viewDropOffCount(struct TripInfo trip[],
                 struct Card passengers[][MAX_PASS],
                 stringDropOff dropOffs[][MAX_DROPOFFS])
{
    stringTrip tripNo;
    
    int tripIndex = -1;

    int passengerCount[MAX_DROPOFFS] = {0};
    
    do
    {
        // Ask user for trip number
        printDropOffTitle();
        
        displayTrips(trip);
        
        printf("Please enter the trip number (AE1xx): ");
        scanf("%5s", tripNo);

        // Check if trip number is valid
        tripIndex = isValidTrip(trip, tripNo);

        if(tripIndex == -1)
        {
            cls();
            printf("\033[0;31mERROR:\033[0m Trip not found or invalid. Please try again.\n\n");
        }
    }
    while(tripIndex == -1);

    // Display the drop-off list and count
    cls();
    printDropOffTitle();
    printf("Drop-off Count for Trip %s\n\n\n", trip[tripIndex].tripNumber);

    printf("%-36s%s\n\n", "Drop-off Point", "Passenger Count");

    displayDropOffCount(trip, tripIndex, passengers, dropOffs, passengerCount);
    
    pressAnyKey();

    cls();
}

// Asks for trip number and displays information of all passengers in the trip sorted by priority number
// @param trip[]           array containing trip information (trip number, etc.)
// @param passengers[][]   array where the passenger information is stored
void
viewPassengerInfo(struct TripInfo trip[],
                  struct Card passengers[][MAX_PASS])
{
    stringTrip tripNo;
    stringFullName fullName;

    int tripIndex = -1;

    int i;

    do
    {
        // Ask user for trip number
        printPassengerInfoTitle();
        
        displayTrips(trip);
        
        printf("Please enter the trip number (AE1xx): ");
        scanf("%5s", tripNo);

        // Check if trip number is valid
        tripIndex = isValidTrip(trip, tripNo);

        if(tripIndex == -1)
        {
            cls();
            printf("\033[0;31mERROR:\033[0m Trip not found or invalid. Please try again.\n\n");
        }
    }
    while(tripIndex == -1);

    // Display information of passengers from selected trip
    cls();
    printPassengerInfoTitle();
    printf("Passengers for Trip %s\n\n", trip[tripIndex].tripNumber);

    printf("%-8s%-46s%-12s%s\n\n", "Seat","Name", "Priority", "ID Number");

    for(i = 0; i < MAX_PASS; i++)
    {
        if(passengers[tripIndex][i].priorityNo != 99)
        {
            // Combine first name and last name
            strcat(strcat(strcpy(fullName, passengers[tripIndex][i].lastName), ", "), passengers[tripIndex][i].firstName);

            printf("%-08d%-46s%-12d%d\n", i + 1,
                                         fullName,
                                         passengers[tripIndex][i].priorityNo,
                                         passengers[tripIndex][i].idNo);
        }
    }

    printf("\n");

    pressAnyKey();

    cls();
}
