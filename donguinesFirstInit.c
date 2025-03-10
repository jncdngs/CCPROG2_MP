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

int
main()
{
    struct Card passengers[MAX_BUS][MAX_PASS];

    struct TripInfo trip[MAX_BUS] = {   // Manila-Laguna
                                        {"AE101", "0600", "MNL-LAG", 0},
                                        {"AE102", "0730", "MNL-LAG", 1},
                                        {"AE103", "0930", "MNL-LAG", 0},
                                        {"AE104", "1100", "MNL-LAG", 1},
                                        {"AE105", "1300", "MNL-LAG", 0},
                                        {"AE106", "1430", "MNL-LAG", 1},
                                        {"AE107", "1530", "MNL-LAG", 0},
                                        {"AE108", "1700", "MNL-LAG", 1},
                                        {"AE109", "1815", "MNL-LAG", 0},
                                        
                                        // Laguna-Manila
                                        {"AE150", "0530", "LAG-MNL", 3},
                                        {"AE151", "0545", "LAG-MNL", 2},
                                        {"AE152", "0700", "LAG-MNL", 3},
                                        {"AE153", "0730", "LAG-MNL", 2},
                                        {"AE154", "0900", "LAG-MNL", 3},
                                        {"AE155", "1100", "LAG-MNL", 2},
                                        {"AE156", "1300", "LAG-MNL", 3},
                                        {"AE157", "1430", "LAG-MNL", 2},
                                        {"AE158", "1530", "LAG-MNL", 3},
                                        {"AE159", "1700", "LAG-MNL", 2},
                                        {"AE160", "1815", "LAG-MNL", 3}
                                    };

    stringDropOff dropOffs[MAX_DROPOFFS][MAX_DROPOFFS] = 
                                   {{
                                        "Mamplasan Toll Exit",
                                        "Phase 5, San Jose Village",
                                        "Milagros Del Rosario (MRR) Bldg."
                                    },
                                    {
                                        "Laguna Blvd. Guard House",
                                        "Milagros Del Rosario (MRR) Bldg."
                                    },
                                    {
                                        "Petron Gasoline Station",
                                        "Gate 4: Gokongwei",
                                        "Gate 2: Henry Sy (North)",
                                        "Gate 1: LS Hall (South)"
                                    },
                                    {
                                        "College of St. Benilde (CSB)",
                                        "Gate 4: Gokongwei",
                                        "Gate 2: Henry Sy (North)",
                                        "Gate 1: LS Hall (South)"
                                    }};

    float mainMenuOption, passengerMenuOption, personnelMenuOption;
    char exit = '\0';
    
    initializePassengers(passengers);
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
                    enterPassengerInfo(trip, passengers, dropOffs);
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
                
                printPersonnelTitle();
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
                    viewPassengerCount(trip, passengers);
                }
                else if (personnelMenuOption == 2)  // [2] View drop-off count
                {
                    cls();
                    viewDropOffCount(trip, passengers, dropOffs);
                }
                else if (personnelMenuOption == 3)  // [3] View passenger information
                {
                    cls();
                    viewPassengerInfo(trip, passengers);
                }
                else if (personnelMenuOption == 4)  // [4] Load passenger
                {
                    cls();
                    // Load passenger
                }
                else if (personnelMenuOption == 5)  // [5] Search passenger
                {
                    cls();
                    searchPassenger(trip, passengers, dropOffs);
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
        else if(mainMenuOption == 3)
        {
            cls();

            do
            {
                printTitle();
                printf("Are you sure you want to exit? (Y/N): ");
                if(scanf(" %c", &exit) != 1)
                {
                    cls();
                    clearInputBuffer();
                    printError();
                }
                
                else if(exit != 'Y' && exit != 'y' &&
                        exit != 'N' && exit != 'n')
                {
                    cls();
                    printError();
                }
            }
            while(exit != 'Y' && exit != 'y' &&
                  exit != 'N' && exit != 'n');
            
            cls();
        }
        else // Invalid option
        {
            cls();
            printError();
        }
    }
    while(exit != 'Y' && exit != 'y');

    // Save information to file
    savePassengerInfo(trip, passengers, dropOffs);
    
    cls();
    printTitle();
    
    printf("Thank you for using the Arrows Express Embarkation System!\n\n");
    
    printf("Press any key to exit...");
    getch();

    return 0;
}
