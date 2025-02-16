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

void printDivider()
{
    int i;
    
    for(i = 0; i < 100; i++)
    {
        printf("-");
    }

    printf("\n");
}

void enterPassengerInfo()   // Add parameter (trip number)
{
    int priorityNo;
    char lastName[51];
    char firstName[51];
    int idNo;
    int dropOff;

    printf("Enter passenger information\n\n");

    do
    {
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

    printf("Last Name (No spaces, max 50 characters): ");
    scanf("%50s", lastName);
    clearInputBuffer();

    printf("First Name (No spaces, max 50 characters): ");
    scanf("%50s", firstName);
    clearInputBuffer();

    do
    {
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
        printf("Drop-off: ");
        if(scanf("%d", &dropOff) != 1)
        {
            // Prevent loop when entering char
            clearInputBuffer();
            
            // Display error when option is a char/str
            printError();
        }
        
        else if(idNo < 1 || idNo > 4)
        {
            printError();
        }
    }
    while(idNo < 1 || idNo > 4);

    // Display entered information

    // Ask user to check if information is correct

    // If correct, pass to struct
}
