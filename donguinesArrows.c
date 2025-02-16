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
    printf("Invalid option. Please try again.\n\n");
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

void printDivider()
{
    int i;
    
    for(i = 0; i < 100; i++)
    {
        printf("-");
    }

    printf("\n");
}

void initializePassengers(struct Card passengers[MAX_BUS][MAX_PASS])
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

void enterPassengerInfo()   // Add parameter (trip number)
{
    int priorityNo;
    stringName lastName;
    stringName firstName;
    int idNo;
    int dropOff;
    char correctInfo;

    do
    {
        // Ask user for information
        do
        {
            cls();
            printPassengerInfoTitle();
            printf("Please enter the following information\n\n");

            printf("Priority No: ");
            if(scanf("%d", &priorityNo) != 1)
            {
                // Prevent loop when entering char
                clearInputBuffer();
                
                // Display error when option is a char/str
                printError();
            }
            
            else if(priorityNo != 1 && priorityNo != 2 && priorityNo != 3
                && priorityNo != 4 && priorityNo != 5 && priorityNo != 6)
            {
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

        do
        {
            cls();
            printPassengerInfoTitle();
            printf("Please enter the following information\n\n");

            printf("ID No (1xxxxxxx): ");
            if(scanf("%d", &idNo) != 1)
            {
                // Prevent loop when entering char
                clearInputBuffer();
                
                // Display error when option is a char/str
                printError();
            }
            
            else if(idNo < 10000000 || idNo > 12499999)
            {
                printError();
            }
        }
        while(idNo < 10000000 || idNo > 12499999);
        
        do
        {
            cls();
            printPassengerInfoTitle();
            printf("Please enter the following information\n\n");

            printf("Drop-off: ");
            if(scanf("%d", &dropOff) != 1)
            {
                // Prevent loop when entering char
                clearInputBuffer();
                
                // Display error when option is a char/str
                printError();
            }
            
            else if(dropOff != 1 && dropOff != 2 && dropOff != 3 && dropOff != 4)
            {
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
    while(correctInfo != 'Y' && correctInfo != 'y');

    // If incorrect, repeat process
    
    // If correct, pass to struct array (using trip number)
}
