/*******************************************************************************

This is to certify that this project is my own work, based on my personal 
efforts in studying and applying the concepts learned. I have constructed the 
functions and their respective algorithms and corresponding code by myself. The
program was run, tested, and debugged by my own efforts. I further certify that 
I have not copied in part or whole or otherwise plagiarized the work of other 
students and/or persons.

                                    Jon Chester C. Donguines, DLSU ID# 12413933

*******************************************************************************/

#include <stdio.h>
#include <conio.h>  // for getch()
#include <string.h>

void cls()
{
    printf("\033[H\033[J");
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

void printDivider()
{
    int i;
    
    for(i = 0; i < 100; i++)
    {
        printf("-");
    }

    printf("\n");
}

int main()
{
    char mainMenuOption, passengerMenuOption, personnelMenuOption;
    
    cls();

    do
    {
        printTitle();
        printf("[1] Passenger\n");
        printf("[2] Arrows Express Personnel\n");
        printf("[3] Exit\n\n");
        printf("Enter option: ");
        scanf(" %c", &mainMenuOption);
        
        switch(mainMenuOption)
        {
            case '1':
                cls();
                
                do
                {
                    printf("Passenger\n\n");
                    printf("[1] Enter passenger information\n");
                    printf("[2] Back to main menu\n");
                    printf("Enter option: ");
                    scanf(" %c", &passengerMenuOption);
                    
                    switch(passengerMenuOption)
                    {
                        case '1': // [1] Enter passenger information
                            cls();
                            // Enter passenger information
                            break;

                        case '2': // [2] Back to main menu
                            cls();
                            break;

                        default: // Invalid option
                            cls();
                            printf("Invalid option. Please try again.\n\n");
                            break;
                    }
                }
                while(passengerMenuOption != '2');

                break;

            case '2':
                cls();
                
                do
                {
                    printf("Arrows Express Personnel\n\n");
                    printf("[1] View passenger count\n");
                    printf("[2] View drop-off count\n");
                    printf("[3] View passenger information\n");
                    printf("[4] Load passenger\n");
                    printf("[5] Search passenger\n");
                    printf("[6] Load recent trip file\n");
                    printf("[7] Back to main menu\n\n");
                    printf("Enter option: ");
                    scanf(" %c", &personnelMenuOption);

                    switch(personnelMenuOption)
                    {
                        case '1': // [1] View passenger count
                            cls();
                            // View passenger count
                            break;

                        case '2': // [2] View drop-off count
                            cls();
                            // View drop-off count
                            break;

                        case '3': // [3] View passenger information
                            cls();
                            // View passenger information
                            break;

                        case '4': // [4] Load passenger
                            cls();
                            // Load passenger
                            break;

                        case '5': // [5] Search passenger
                            cls();
                            // Search passenger
                            break;

                        case '6': // [6] Load recent trip file
                            cls();
                            // Load recent trip file
                            break;

                        case '7': // [7] Back to main menu
                            cls();
                            break;

                        default: // Invalid option
                            cls();
                            printf("Invalid option. Please try again.\n\n");
                            break;
                    }
                }
                while(personnelMenuOption != '7');
                
                break;
        }

        if(mainMenuOption < '1' || mainMenuOption > '3')
        {
            cls();
            printf("Invalid option. Please try again.\n\n");
        }

    }
    while(mainMenuOption != '3');
    
    cls();
    printf("Thank you for using the Arrows Express Embarkation System!\n\n");
    printf("Press any key to exit...");
    getch();

    return 0;
}
