#include <stdio.h>
#include <conio.h>  // for getch()
#include <string.h>
#include "donguinesArrows.h"

void cls()
{
    printf("\033[H\033[J");
}

void clearInputBuffer()
{
    while(getchar() != '\n');
}

void printError()
{
    printf("\033[0;31mERROR: \033[0m");
    printf("Invalid entry. Please try again.\n\n");
}

void printTitle()
{
    printf(" ______          _                                     _____                                  __\n");
    printf(" \\ \\ \\ \\        / \\   _ __ _ __ _____      _____      | ____|_  ___ __  _ __ ___  ___ ___     \\ \\\n");
    printf("  \\ \\ \\ \\_____ / _ \\ | '__| '__/ _ \\ \\ /\\ / / __|_____|  _| \\ \\/ / '_ \\| '__/ _ \\/ __/ __|_____\\ \\\n");
    printf("  / / / /_____/ ___ \\| |  | | | (_) \\ V  V /\\__ \\_____| |___ >  <| |_) | | |  __/\\__ \\__ \\_____/ /\n");
    printf(" /_/_/_/     /_/   \\_\\_|  |_|  \\___/ \\_/\\_/ |___/     |_____/_/\\_\\ .__/|_|  \\___||___/___/    /_/\n");
    printf("                                                                 |_|\n\n");
}

void printPassengerTitle()
{
    printf(" ______        ____                                             __\n");
    printf(" \\ \\ \\ \\      |  _ \\ __ _ ___ ___  ___ _ __   __ _  ___ _ __    \\ \\\n");
    printf("  \\ \\ \\ \\_____| |_) / _` / __/ __|/ _ \\ '_ \\ / _` |/ _ \\ '__|____\\ \\\n");
    printf("  / / / /_____|  __/ (_| \\__ \\__ \\  __/ | | | (_| |  __/ | |_____/ /\n");
    printf(" /_/_/_/      |_|   \\__,_|___/___/\\___|_| |_|\\__, |\\___|_|      /_/\n");
    printf("                                             |___/\n\n");
}

void printPassengerInfoTitle()
{
    printf(" ______        ____                                              ___        __           __\n");
    printf(" \\ \\ \\ \\      |  _ \\ __ _ ___ ___  ___ _ __   __ _  ___ _ __    |_ _|_ __  / _| ___      \\ \\\n");
    printf("  \\ \\ \\ \\_____| |_) / _` / __/ __|/ _ \\ '_ \\ / _` |/ _ \\ '__|____| || '_ \\| |_ / _ \\ _____\\ \\\n");
    printf("  / / / /_____|  __/ (_| \\__ \\__ \\  __/ | | | (_| |  __/ | |_____| || | | |  _| (_) |_____/ /\n");
    printf(" /_/_/_/      |_|   \\__,_|___/___/\\___|_| |_|\\__, |\\___|_|      |___|_| |_|_|  \\___/     /_/\n");
    printf("                                             |___/\n\n");
}

void printPassengerCountTitle()
{
    printf(" ______        ____                                                ____                  _      __\n");
    printf(" \\ \\ \\ \\      |  _ \\ __ _ ___ ___  ___ _ __   __ _  ___ _ __      / ___|___  _   _ _ __ | |_    \\ \\\n");
    printf("  \\ \\ \\ \\_____| |_) / _` / __/ __|/ _ \\ '_ \\ / _` |/ _ \\ '__|____| |   / _ \\| | | | '_ \\| __|____\\ \\\n");
    printf("  / / / /_____|  __/ (_| \\__ \\__ \\  __/ | | | (_| |  __/ | |_____| |__| (_) | |_| | | | | ||_____/ /\n");
    printf(" /_/_/_/      |_|   \\__,_|___/___/\\___|_| |_|\\__, |\\___|_|        \\____\\___/ \\__,_|_| |_|\\__|   /_/\n");
    printf("                                             |___/\n\n");
}

void printPersonnelTitle()
{
    printf(" ______        ____                                      _     __\n");
    printf(" \\ \\ \\ \\      |  _ \\ ___ _ __ ___  ___  _ __  _ __   ___| |    \\ \\\n");
    printf("  \\ \\ \\ \\_____| |_) / _ \\ '__/ __|/ _ \\| '_ \\| '_ \\ / _ \\ |_____\\ \\\n");
    printf("  / / / /_____|  __/  __/ |  \\__ \\ (_) | | | | | | |  __/ |_____/ /\n");
    printf(" /_/_/_/      |_|   \\___|_|  |___/\\___/|_| |_|_| |_|\\___|_|    /_/\n\n\n");
}

void initializePassengers(struct Card passengers[][MAX_PASS])
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

int isValidTrip(stringTrip trip[], stringTrip tripNo)
{
    int i;
    int tripIndex = -1;

    for(i = 0; i < MAX_BUS; i++)
    {
        if(strcmp(trip[i], tripNo) == 0)
        {
            tripIndex = i;
        }
    }

    return tripIndex;
}

int isFullTrip(int tripIndex, struct Card passengers[][MAX_PASS])
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

int getEmptySeat(int tripIndex, struct Card passengers[][MAX_PASS])
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

void enterPassengerInfo(stringTrip trip[], struct Card passengers[][MAX_PASS])
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
    
                printf("Priority No: ");
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
    
                printf("ID No (1xxxxxxx): ");
                if(scanf("%d", &idNo) != 1)
                {
                    // Prevent loop when entering char
                    clearInputBuffer();
                    
                    // Display error when option is a char/str
                    cls();
                    printError();
                }
                
                else if(idNo < 10000000 || idNo > 12499999)
                {
                    cls();
                    printError();
                }
            }
            while(idNo < 10000000 || idNo > 12499999);
            
            cls();
            do
            {
                printPassengerInfoTitle();
                printf("Please enter the following information\n\n");
    
                printf("Drop-off: ");
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
            printf("ID No:       %d\n", idNo);
            printf("Drop-off:    %d\n\n", dropOff);
    
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

void viewPassengerCount(stringTrip trip[], struct Card passengers[][MAX_PASS])
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
    printf("Seat Map for Trip %s\n\n", trip[tripIndex]);
    
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