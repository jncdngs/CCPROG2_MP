#include <stdio.h>
#include <conio.h>
#include "donguinesArrows.h"

/**
 * Asks for trip number and passenger information and assigns user a seat if the trip is not full.
 * 
 * @param trip[]            array containing trip information (trip number, etc.)
 * @param passengers[][]    array where all the passenger info is stored
 * @param dropOffs[][]      array containing full names of drop-off points
 * @param specDeployed      flag that specifies if special trips were deployed
 */
void
enterPassengerInfo(struct TripInfo trip[],
                   struct Card passengers[][SPECIAL_PASS],
                   stringDropOff dropOffs[][MAX_DROPOFFS],
                   int *specDeployed)
{
    stringTrip tripNo;
    
    int tripIndex = -1;
    int dropOffCount[MAX_DROPOFFS] = {3, 2, 4, 4};
    char correctInfo = '\0';
    int validID = 0;

    struct Card temp = {99, "", "", 0, 0};

    // Display disclaimer
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
        printPassengerInfoTitle();
        
        displayTrips(trip, *specDeployed);
        
        // Ask user for trip number
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
        
        // Ask user for priority number
        printf("Please enter type of passenger: ");
        if(scanf("%d", &temp.priorityNo) != 1)
        {
            // Prevent loop when entering char
            clearInputBuffer();
            
            // Display error when option is a char/str
            cls();
            printError();
        }
        else if(temp.priorityNo < 1 || temp.priorityNo > 6)
        {
            cls();
            printError();
        }
    }
    while(temp.priorityNo < 1 || temp.priorityNo > 6);

    // Check if there are seats available or if priority is higher than last passenger in the trip
    if(isFullTrip(tripIndex, passengers, temp.priorityNo) == 2)
    {
        cls();
        printPassengerInfoTitle();
        printf("The selected trip is full.\n\n");

        pressAnyKey();

        tripIndex = -1;
    }
    else
    {
        do
        {       
            // Ask user for other information
            cls();
            printPassengerInfoTitle();
            printf("Please enter the following information\n\n");
            printf("Last Name (No spaces, max %d characters): ", MAX_CHARS - 1);
            scanf("%20s", temp.lastName);
            clearInputBuffer();
    
            cls();
            printPassengerInfoTitle();
            printf("Please enter the following information\n\n");
            printf("First Name (No spaces, max %d characters): ", MAX_CHARS - 1);
            scanf("%20s", temp.firstName);
            clearInputBuffer();
    
            cls();
            do
            {
                printPassengerInfoTitle();
                printf("Please enter the following information\n\n");
                printf("Please enter your ID Number (xxxxxxxx): ");
                if(scanf("%d", &temp.idNo) != 1)
                {
                    // Prevent loop when entering char
                    clearInputBuffer();
                    
                    // Display error when option is a char/str
                    cls();
                    printError();
                }
                else if((validID = isValidID(passengers, temp.idNo)) == 0)
                {
                    cls();
                    printError();
                }
                else if(validID == 2)
                {
                    cls();
                    printf("\033[0;31mERROR: \033[0m");
                    printf("Duplicate ID. Please try again.\n\n");
                }
            }
            while(validID == 0 || validID == 2);
            
            cls();
            do
            {
                printPassengerInfoTitle();
                printf("Please enter the following information\n\n");

                displayDropOffs(trip, tripIndex, dropOffs);
    
                printf("Please select a drop-off point: ");
                if(scanf("%d", &temp.dropOff) != 1)
                {
                    // Prevent loop when entering char
                    clearInputBuffer();
                    
                    // Display error when option is a char/str
                    cls();
                    printError();
                }
                else if(temp.dropOff < 1 || temp.dropOff > dropOffCount[trip[tripIndex].dropOffSet])
                {
                    cls();
                    printError();
                }
            }
            while(temp.dropOff < 1 || temp.dropOff > dropOffCount[trip[tripIndex].dropOffSet]);
    
            // Display entered information
            cls();
            printPassengerInfoTitle();
            printf("Here is the information you entered:\n\n");
            printf("Priority No: %d\n", temp.priorityNo);
            printf("Last Name:   %s\n", temp.lastName);
            printf("First Name:  %s\n", temp.firstName);
            printf("ID Number:   %08d\n", temp.idNo);
            printf("Drop-off:    %s\n\n", dropOffs[trip[tripIndex].dropOffSet][temp.dropOff - 1]);
    
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
                    printError();
            }
            while(correctInfo != 'Y' && correctInfo != 'y' &&
                  correctInfo != 'N' && correctInfo != 'n');
        }
        while(correctInfo != 'Y' && correctInfo != 'y');    // If incorrect, repeat process
        
        // Tell user that information has been saved
        cls();
        printPassengerInfoTitle();
        
        // Check if a lower priority passenger will be moved
        if(isFullTrip(tripIndex, passengers, temp.priorityNo) == 1)
        {
            movePassenger(trip, passengers, tripIndex);
            printf("Lower priority passenger has been moved.\n\n");
        }
        
        // Insert the new passenger into the passengers array
        insertPassenger(passengers, tripIndex, temp);
        
        printf("Information has been saved.\n\n");
        
        pressAnyKey();
    }

    cls();
}
