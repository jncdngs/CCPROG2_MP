#include <stdio.h>
#include <conio.h>  // for getch()
#include <string.h>
#include "donguinesArrows.h"

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
        if(passengers[tripIndex][i].priorityNo != 0)
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

    printf("Press any key to return to the main menu...");
    getch();

    cls();
}

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

    cls();
    printDropOffTitle();
    printf("Drop-off Count for Trip %s\n\n\n", trip[tripIndex].tripNumber);

    printf("%-36s%s\n\n", "Drop-off Point", "Passenger Count");

    displayDropOffCount(trip, tripIndex, passengers, dropOffs, passengerCount);
    
    printf("Press any key to return to the main menu...");
    getch();

    cls();
}
