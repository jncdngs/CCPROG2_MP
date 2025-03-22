#include <stdio.h>
#include <conio.h>  // for getch()
#include "donguinesArrows.h"

/**
 * Asks for trip number and passenger information and assigns user a seat if the trip is not full.
 * 
 * @param trip[]           array containing trip information (trip number, etc.)
 * @param passengers[][]   array where the passenger information is stored
 * @param dropOffs[][]     array containing full names of drop-off points
 */
void
enterPassengerInfo(struct TripInfo trip[],
                   struct Card passengers[][MAX_PASS],
                   stringDropOff dropOffs[][MAX_DROPOFFS])
{
    stringTrip tripNo;
    
    int tripIndex = -1;
    char correctInfo = '\0';

    struct Card temp = {99, "", "", 0, 0};

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

        pressAnyKey();

        tripIndex = -1;
    }
    else
    {
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
                if(scanf("%d", &temp.priorityNo) != 1)
                {
                    // Prevent loop when entering char
                    clearInputBuffer();
                    
                    // Display error when option is a char/str
                    cls();
                    printError();
                }
                
                else if(temp.priorityNo != 1 && temp.priorityNo != 2 && temp.priorityNo != 3
                     && temp.priorityNo != 4 && temp.priorityNo != 5 && temp.priorityNo != 6)
                {
                    cls();
                    printError();
                }
            }
            while(temp.priorityNo != 1 && temp.priorityNo != 2 && temp.priorityNo != 3
               && temp.priorityNo != 4 && temp.priorityNo != 5 && temp.priorityNo != 6);

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
                
                else if(temp.idNo < 0 || temp.idNo > 99999999)
                {
                    cls();
                    printError();
                }
            }
            while(temp.idNo < 0 || temp.idNo > 99999999);
            
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
                
                else if(temp.dropOff != 1 && temp.dropOff != 2 && temp.dropOff != 3 && temp.dropOff != 4)
                {
                    cls();
                    printError();
                }
            }
            while(temp.dropOff != 1 && temp.dropOff != 2 && temp.dropOff != 3 && temp.dropOff != 4);
    
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
        
        // If correct, pass to struct array (using trip number)
        // Insert based on priority number
        insertPassenger(passengers, tripIndex, temp);

        // Tell user that information has been saved
        cls();
        printPassengerInfoTitle();
        
        printf("Information has been saved.\n\n");
        
        pressAnyKey();
    }

    cls();
}
