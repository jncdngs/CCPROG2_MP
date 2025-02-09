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
    printf("  \\ \\ \\ \\_____| |_) / _` / __/ __|/ _ \\ '_ \\ / _` |/ _ \\ '__|_____\\ \\\n");
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

void enterPassengerInfo()
{
    Card passenger;
    
    printf("Enter passenger information\n\n");

    printf("Priority No: ");
    if(scanf("%d", &passenger.priorityNo) != 1)
    {
        // Prevent loop when entering char
        clearInputBuffer();
        
        // Display error when option is a char/str
        printError();
    }
    
    else if(passenger.priorityNo != 1 && passenger.priorityNo != 2
         && passenger.priorityNo != 3 && passenger.priorityNo != 4
         && passenger.priorityNo != 5 && passenger.priorityNo != 6)
    {
        printError();
    }

    printf("Last Name (Do NOT use spaces): ");
    scanf("%s", passenger.lastName);
    clearInputBuffer();

    printf("First Name (Do NOT use spaces): ");
    scanf("%s", passenger.firstName);
    clearInputBuffer();
    
    printf("ID No: ");
    scanf("%d", &passenger.idNo);
    clearInputBuffer();

    printf("Drop-off: ");
    scanf("%d", passenger.dropOff);
    clearInputBuffer();

    printf("%d\n%s\n%s\n%d\n%d\n\n\n", passenger.priorityNo, 
                                       passenger.lastName, 
                                       passenger.firstName, 
                                       passenger.idNo, 
                                       passenger.dropOff);
}