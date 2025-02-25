#include <stdio.h>
#include <conio.h>  // for getch()
#include <string.h>
#include "donguinesArrows.h"

void
initializePassengers(struct Card passengers[][MAX_PASS])
{
    int i, j;

    for(i = 0; i < MAX_BUS; i++)
    {
        for(j = 0; j < MAX_PASS; j++)
        {
            passengers[i][j].priorityNo = 0;
            strcpy(passengers[i][j].lastName, "");
            strcpy(passengers[i][j].firstName, "");
            passengers[i][j].idNo = 0;
            passengers[i][j].dropOff = 0;
        }
    }
}

int
isValidTrip(struct TripInfo trip[],
            stringTrip tripNo)
{
    int i;
    int tripIndex = -1;

    for(i = 0; i < MAX_BUS; i++)
    {
        if(strcmp(trip[i].tripNumber, tripNo) == 0)
        {
            tripIndex = i;
        }
    }

    return tripIndex;
}

int
isFullTrip(int tripIndex,
           struct Card passengers[][MAX_PASS])
{
    int i;
    int passengerCount = 0;
    int isFull = 0;

    for(i = 0; i < MAX_PASS; i++)
    {
        if(passengers[tripIndex][i].priorityNo != 0)
        {
            passengerCount++;
        }
    }

    if(passengerCount == MAX_PASS)
    {
        isFull = 1;
    }

    return isFull;
}

int
getEmptySeat(int tripIndex,
             struct Card passengers[][MAX_PASS])
{
    int i;
    int found = 0;
    int emptySeat = -1;

    for(i = 0; i < MAX_PASS; i++)
    {
        if(passengers[tripIndex][i].priorityNo == 0 && !found)
        {
            emptySeat = i;
            found = 1;
        }
    }

    return emptySeat;
}

void
displayTrips(struct TripInfo trip[])
{
    int i;
    int rowsMax = 11;
    int firstRouteCount = 9;
    
    printf("%-10s%-9s%-17s", "Trip", "Time", "Route");
    printf("%-10s%-9s%s\n\n", "Trip", "Time", "Route");

    for(i = 0; i < rowsMax; i++)
    {
        // Display trips from first route (first 3 columns)
        if(trip[i].dropOffSet == 0 || trip[i].dropOffSet == 1)
        {
            printf("%-10s%-9s%-17s", trip[i].tripNumber,
                                     trip[i].tripTime,
                                     trip[i].tripRoute);
        }
        else    // Print spaces if first route has less trips than second route
        {
            printf("%36s", "");
        }

        // Display trips from second route (next 3 columns)
        if(trip[i + firstRouteCount].dropOffSet == 2 || trip[i + firstRouteCount].dropOffSet == 3)
        {
            printf("%-10s%-9s%s\n", trip[i + firstRouteCount].tripNumber,
                                    trip[i + firstRouteCount].tripTime,
                                    trip[i + firstRouteCount].tripRoute);
        }
    }

    printf("\n");
}

void
displayDropOffs(struct TripInfo trip[],
                int tripIndex,
                stringDropOff dropOffs[][4])
{
    int i;
    int dropOffCount = 4;

    for(i = 0; i < dropOffCount; i++)
    {
        printf("[%d] %s\n", i + 1, dropOffs[trip[tripIndex].dropOffSet][i]);

        if(strcmp(dropOffs[trip[tripIndex].dropOffSet][i + 1], "") == 0)
        {
            i = dropOffCount;
        }
    }

    printf("\n");
}

void
enterPassengerInfo(struct TripInfo trip[],
                   struct Card passengers[][MAX_PASS],
                   stringDropOff dropOffs[][4])
{
    stringTrip tripNo;
    stringName lastName;
    stringName firstName;
    
    int tripIndex = -1;
    int seatIndex = -1;

    int priorityNo = 0;
    int idNo = 0;
    int dropOff = 0;
    char correctInfo = '\0';

    strcpy(lastName, "");
    strcpy(firstName, "");

    // Display disclaimer (can be moved to next trip or removed)
    printPassengerInfoTitle();
    printf("\033[0;31mDISCLAIMER: \033[0m\n\n");
    printf("This system automatically assigns you to a seat on your selected trip.\n");
    printf("In case trip you selected is full, you will be notified.\n\n");
    printf("In the event that a trip is full and a higher priority user wants to board,\n");
    printf("the first lowest priority passenger listed will be moved to the next trip.\n\n");

    // Ask user to acknowledge disclaimer
    printf("Press any key to acknowledge and continue...");
    getch();
    
    cls();
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

    // If valid, check if trip is full
    if(isFullTrip(tripIndex, passengers))
    {
        cls();
        printPassengerInfoTitle();
        printf("The selected trip is full.\n\n");
        printf("Press any key to return to the main menu...");
        getch();
        tripIndex = -1;
    }
    else
    {
        seatIndex = getEmptySeat(tripIndex, passengers);
        
        do
        {       
            // Ask user for information
            cls();
            do
            {
                printPassengerInfoTitle();
                printf("Please enter the following information\n\n");

                printf("[1] Faculty / ASF with Inter-Campus Assignments\n");
                printf("[2] Student with Inter-Campus Subjects\n");
                printf("[3] Researcher\n");
                printf("[4] School Administrator\n");
                printf("[5] University Fellow\n");
                printf("[6] Employee / Student with Official Business\n\n");
    
                printf("Please enter type of passenger: ");
                if(scanf("%d", &priorityNo) != 1)
                {
                    // Prevent loop when entering char
                    clearInputBuffer();
                    
                    // Display error when option is a char/str
                    cls();
                    printError();
                }
                
                else if(priorityNo != 1 && priorityNo != 2 && priorityNo != 3
                    && priorityNo != 4 && priorityNo != 5 && priorityNo != 6)
                {
                    cls();
                    printError();
                }
            }
            while(priorityNo != 1 && priorityNo != 2 && priorityNo != 3
            && priorityNo != 4 && priorityNo != 5 && priorityNo != 6);
    
            cls();
            printPassengerInfoTitle();
            printf("Please enter the following information\n\n");
            printf("Last Name (No spaces, max 50 characters): ");
            scanf("%50s", lastName);
            clearInputBuffer();
    
            cls();
            printPassengerInfoTitle();
            printf("Please enter the following information\n\n");
            printf("First Name (No spaces, max 50 characters): ");
            scanf("%50s", firstName);
            clearInputBuffer();
    
            cls();
            do
            {
                printPassengerInfoTitle();
                printf("Please enter the following information\n\n");
    
                printf("Please enter your ID Number (1xxxxxxx): ");
                if(scanf("%d", &idNo) != 1)
                {
                    // Prevent loop when entering char
                    clearInputBuffer();
                    
                    // Display error when option is a char/str
                    cls();
                    printError();
                }
                
                else if(idNo < 10000000 || idNo > 19999999)
                {
                    cls();
                    printError();
                }
            }
            while(idNo < 10000000 || idNo > 19999999);
            
            cls();
            do
            {
                printPassengerInfoTitle();
                printf("Please enter the following information\n\n");

                displayDropOffs(trip, tripIndex, dropOffs);
    
                printf("Please select a drop-off point: ");
                if(scanf("%d", &dropOff) != 1)
                {
                    // Prevent loop when entering char
                    clearInputBuffer();
                    
                    // Display error when option is a char/str
                    cls();
                    printError();
                }
                
                else if(dropOff != 1 && dropOff != 2 && dropOff != 3 && dropOff != 4)
                {
                    cls();
                    printError();
                }
            }
            while(dropOff != 1 && dropOff != 2 && dropOff != 3 && dropOff != 4);
    
            // Display entered information
            cls();
            printPassengerInfoTitle();
            printf("Here is the information you entered:\n\n");
            printf("Priority No: %d\n", priorityNo);
            printf("Last Name:   %s\n", lastName);
            printf("First Name:  %s\n", firstName);
            printf("ID Number:   %d\n", idNo);
            printf("Drop-off:    %s\n\n", dropOffs[trip[tripIndex].dropOffSet][dropOff - 1]);
    
            // Ask user to check if information is correct
            do
            {
                printf("Is the information correct? (Y/N): ");
                if(scanf(" %c", &correctInfo) != 1)
                {
                    clearInputBuffer();
                    printError();
                }
                
                else if(correctInfo != 'Y' && correctInfo != 'y' &&
                        correctInfo != 'N' && correctInfo != 'n')
                {
                    printError();
                }
            }
            while(correctInfo != 'Y' && correctInfo != 'y' &&
                correctInfo != 'N' && correctInfo != 'n');
        }
        while(correctInfo != 'Y' && correctInfo != 'y');    // If incorrect, repeat process
        
        // If correct, pass to struct array (using trip number)
        passengers[tripIndex][seatIndex].priorityNo = priorityNo;
        strcpy(passengers[tripIndex][seatIndex].lastName, lastName);
        strcpy(passengers[tripIndex][seatIndex].firstName, firstName);
        passengers[tripIndex][seatIndex].idNo = idNo;
        passengers[tripIndex][seatIndex].dropOff = dropOff;

        // Tell user that information has been saved
        cls();
        printPassengerInfoTitle();
        printf("Information has been saved.\n\n");
        printf("Press any key to return to the main menu...");
        getch();
    }

    cls();
}

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
