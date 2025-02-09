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
#include "donguinesArrows.h"

int main()
{
    float mainMenuOption, passengerMenuOption, personnelMenuOption;
    
    cls();

    do
    {
        mainMenuOption = 0;         // Initialize to zero (invalid by default)
        
        printTitle();
        printf("[1] Passenger\n");
        printf("[2] Arrows Express Personnel\n");
        printf("[3] Exit\n\n");
        printf("Enter option: ");

        if(scanf("%f", &mainMenuOption) != 1)
        {
            // Prevent loop when entering char
            clearInputBuffer();
            
            // Display error when option is a char/str
            cls();
            printError();
        }

        // Explicitly invalidate non-integers
        else if(mainMenuOption != 1 && mainMenuOption != 2 && mainMenuOption != 3)
        {
            cls();
            printError();
        }

        if(mainMenuOption == 1) // Passenger
        {
            cls();
            
            do
            {
                passengerMenuOption = 0;    // Initialize to zero (invalid by default)
                
                printPassengerTitle();
                printf("[1] Enter passenger information\n");
                printf("[2] Back to main menu\n\n");
                printf("Enter option: ");

                if(scanf("%f", &passengerMenuOption) != 1)
                {
                    // Prevent loop when entering char
                    clearInputBuffer();
                    
                    // Display error when option is a char/str
                    cls();
                    printError();
                }
            
                // Display error when option is an invalid number
                else if(passengerMenuOption != 1 && passengerMenuOption != 2)
                {
                    cls();
                    printError();
                }
                
                if(passengerMenuOption == 1)        // [1] Enter passenger information
                {
                    cls();
                    enterPassengerInfo();
                }
                else if(passengerMenuOption == 2)   // [2] Back to main menu
                {
                    cls();
                }
                else                                // Invalid option
                {
                    cls();
                    printError();
                }
            }
            while(passengerMenuOption != 2);
        }
        else if(mainMenuOption == 2) // Arrows Express Personnel
        {
            cls();
            
            do
            {
                personnelMenuOption = 0;    // Initialize to zero (invalid by default)
                
                printf("Arrows Express Personnel\n\n");
                printf("[1] View passenger count\n");
                printf("[2] View drop-off count\n");
                printf("[3] View passenger information\n");
                printf("[4] Load passenger\n");
                printf("[5] Search passenger\n");
                printf("[6] Load recent trip file\n");
                printf("[7] Back to main menu\n\n");
                printf("Enter option: ");

                if(scanf("%f", &personnelMenuOption) != 1)
                {
                    // Prevent loop when entering char
                    clearInputBuffer();
                    
                    // Display error when option is a char/str
                    cls();
                    printError();
                }
            
                // Display error when option is an invalid number
                else if(personnelMenuOption != 1 && personnelMenuOption != 2
                     && personnelMenuOption != 3 && personnelMenuOption != 4
                     && personnelMenuOption != 5 && personnelMenuOption != 6
                     && personnelMenuOption != 7)
                {
                    cls();
                    printError();
                }

                if (personnelMenuOption == 1)       // [1] View passenger count
                {
                    cls();
                    // View passenger count
                }
                else if (personnelMenuOption == 2)  // [2] View drop-off count
                {
                    cls();
                    // View drop-off count
                }
                else if (personnelMenuOption == 3)  // [3] View passenger information
                {
                    cls();
                    // View passenger information
                }
                else if (personnelMenuOption == 4)  // [4] Load passenger
                {
                    cls();
                    // Load passenger
                }
                else if (personnelMenuOption == 5)  // [5] Search passenger
                {
                    cls();
                    // Search passenger
                }
                else if (personnelMenuOption == 6)  // [6] Load recent trip file
                {
                    cls();
                    // Load recent trip file
                }
                else if (personnelMenuOption == 7)  // [7] Back to main menu
                {
                    cls();
                }
                else                                // Invalid option
                {
                    cls();
                    printError();
                }
            }
            while(personnelMenuOption != 7);
        }
        else // Invalid option
        {
            cls();
            printError();
        }
    }
    while(mainMenuOption != 3);
    
    cls();
    printf("Thank you for using the Arrows Express Embarkation System!\n\n");
    printf("Press any key to exit...");
    getch();

    return 0;
}