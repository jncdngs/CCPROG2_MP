#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "donguinesArrows.h"

/**
 * Asks for trip number and displays the seat map and passenger count for the trip.
 * 
 * @param trip[]           array containing trip information (trip number, etc.)
 * @param passengers[][]   array where the passenger info in regular trips is stored
 */
void
viewPassengerCount(struct TripInfo trip[],
                   struct Card passengers[][SPECIAL_PASS])
{
    stringTrip tripNo;

    int tripIndex = -1;

    int passengerCount = 0;
    int seatsAvail = MAX_PASS;
    char seatStatus[SPECIAL_PASS];

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
    for(i = 0; i < SPECIAL_PASS; i++)
    {
        if(passengers[tripIndex][i].priorityNo != 99)
        {
            seatStatus[i] = 'X';
            passengerCount++;
        }
        else
            seatStatus[i] = 'O';
    }

    // Display seat map
    cls();
    printPassengerCountTitle();
    printf("Seat Map for Trip %s\n\n", trip[tripIndex].tripNumber);
    
    if(passengerCount <= MAX_PASS)
    {
        for(i = 0; i < 9; i++)
        {
            if(i % 2)
            {
                for(j = 0; j < 3; j++)
                    printf("| %c ", seatStatus[(i / 2 * 3) + j]);
    
                printf("|");
            }
            else
                printf("+---+---+---+");
    
            printf("\n");
        }
        printf("| %c |       |\n", seatStatus[12]);
        printf("+---+---+---+\n\n");
    }
    else
    {
        for(i = 0; i < 7; i++)
        {
            if(i % 2)
            {
                for(j = 0; j < 4; j++)
                    printf("| %c ", seatStatus[(i - 1) * 2 + j]);
    
                printf("|");
            }
            else
                printf("+---+---+---+---+");
    
            printf("\n");
        }
        printf("|   | %c | %c | %c |\n", seatStatus[12],
                                         seatStatus[13],
                                         seatStatus[14]);
        printf("+---+---+---+---+\n");
        printf("|   %c   |       |\n", seatStatus[15]);
        printf("+---+---+---+---+\n\n");

        seatsAvail = SPECIAL_PASS;
    }

    printf("Seats taken:     %d\n", passengerCount);
    printf("Seats available: %d\n\n", seatsAvail - passengerCount);

    pressAnyKey();
    cls();
}

/**
 * Asks for trip number and displays drop-off points for the trip with corresponding passenger counts.
 * 
 * @param trip[]           array containing trip information (trip number, etc.)
 * @param passengers[][]   array where the passenger info in regular trips is stored
 * @param dropOffs[][]     array containing full names of drop-off points
 */
void
viewDropOffCount(struct TripInfo trip[],
                 struct Card passengers[][SPECIAL_PASS],
                 stringDropOff dropOffs[][MAX_DROPOFFS])
{
    stringTrip tripNo;
    
    int tripIndex = -1;

    int passengerCount[MAX_DROPOFFS] = {0};
    
    do
    {
        // Ask user for trip number
        printDropOffTitle();
        
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

    // Display the drop-off list and count
    cls();
    printDropOffTitle();
    printf("Drop-off Count for Trip %s\n\n", trip[tripIndex].tripNumber);

    printf("%-36s%s\n\n", "Drop-off Point", "Passenger Count");

    displayDropOffCount(trip, tripIndex, passengers, dropOffs, passengerCount);
    
    pressAnyKey();
    cls();
}

/**
 * Asks for trip number and displays information of all passengers in the trip sorted by priority number.
 * 
 * @param trip[]           array containing trip information (trip number, etc.)
 * @param passengers[][]   array where the passenger info in regular trips is stored
 */
void
viewPassengerInfo(struct TripInfo trip[],
                  struct Card passengers[][SPECIAL_PASS])
{
    stringTrip tripNo;
    stringFullName fullName;

    int tripIndex = -1;

    int i;

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

    // Display information of passengers from selected trip
    cls();
    printPassengerInfoTitle();

    if(passengers[tripIndex][0].priorityNo != 99)
    {
        printf("Passengers for Trip %s\n\n", trip[tripIndex].tripNumber);
        printf("%-8s%-46s%-12s%s\n\n", "Seat","Name", "Priority", "ID Number");
    }
    else
        printf("Trip %s has no passengers.\n", trip[tripIndex].tripNumber);

    for(i = 0; i < SPECIAL_PASS; i++)
    {
        if(passengers[tripIndex][i].priorityNo != 99)
        {
            // Combine first name and last name
            strcat(strcat(strcpy(fullName, passengers[tripIndex][i].lastName), ", "), passengers[tripIndex][i].firstName);

            printf("%-8d%-46s%-12d%08d\n", i + 1,
                                         fullName,
                                         passengers[tripIndex][i].priorityNo,
                                         passengers[tripIndex][i].idNo);
        }
    }

    printf("\n");

    pressAnyKey();
    cls();
}

/**
 * Loads passenger info from passenger.txt and assigns it to the corresponding trip.
 * 
 * @param trip[]           array containing trip information (trip number, etc.)
 * @param passengers[][]   array where the passenger info in regular trips is stored
 * @param dropOffs[][]     array containing full names of drop-off points
 */
void
loadPassenger(struct TripInfo trip[],
              struct Card passengers[][SPECIAL_PASS],
              stringDropOff dropOffs[][MAX_DROPOFFS])
{
    stringTrip tripNo;
    stringFileName fileName = "passenger.txt";
    int tripIndex = -1;
    char correctInfo = '\0';

    struct Card temp = {99, "", "", 0, 0};

    // Read contents of the file
    FILE *file;

    file = fopen(fileName, "r");

    if(file != NULL)
    {
        fscanf(file, "%s", tripNo);
        fscanf(file, "%d", &temp.priorityNo);
        fscanf(file, "%s", temp.lastName);
        fscanf(file, "%s", temp.firstName);
        fscanf(file, "%d", &temp.idNo);
        fscanf(file, "%d", &temp.dropOff);
        cls();

        // Ask user to check if information is correct
        do
        {
            printLoadPassengerTitle();
            printf("Here is the information stored in the file:\n\n");
            printf("Trip No:     %s\n", tripNo);
            printf("Priority No: %d\n", temp.priorityNo);
            printf("Last Name:   %s\n", temp.lastName);
            printf("First Name:  %s\n", temp.firstName);
            printf("ID Number:   %08d\n", temp.idNo);
            printf("Drop-off:    %d - %s\n\n", temp.dropOff,
                                               dropOffs[trip[tripIndex].dropOffSet][temp.dropOff - 1]);
            
            printf("Do you want to enter this information to the system? (Y/N): ");
            if(scanf(" %c", &correctInfo) != 1)
            {
                clearInputBuffer();
                printError();
                cls();
            }
            else if(correctInfo != 'Y' && correctInfo != 'y' &&
                    correctInfo != 'N' && correctInfo != 'n')
            {
                printError();
                cls();
            }
        }
        while(correctInfo != 'Y' && correctInfo != 'y' &&
              correctInfo != 'N' && correctInfo != 'n');

        if(correctInfo == 'Y' || correctInfo == 'y')
        {
            tripIndex = isValidTrip(trip, tripNo);
        
            if(tripIndex == -1)
            {
                cls();
                printf("\033[0;31mERROR:\033[0m Trip not found or invalid. Please try again.\n\n");
            }
    
            fclose(file);
    
            // If valid, check if trip is full
            if(isFullTrip(tripIndex, passengers, temp.priorityNo))
            {
                cls();
                printPassengerInfoTitle();
                printf("The selected trip is full.\n\n");
    
                pressAnyKey();
    
                tripIndex = -1;
            }
            else
            {    
                // If correct, pass to struct array (using trip number)
                // Insert based on priority number
                insertPassenger(passengers, tripIndex, temp);
    
                // Tell user that information has been saved
                cls();
                printLoadPassengerTitle();
                
                printf("Information has been saved.\n\n");
                
                pressAnyKey();
            }
        }
    }
    else
    {
        printLoadPassengerTitle();
        printf("No passenger file found. Please check again.\n\n");

        pressAnyKey();
    }

    cls();
}

/**
 * Asks for last name and displays information of passengers with that last name.
 * 
 * @param trip[]           array containing trip information (trip number, etc.)
 * @param passengers[][]   array where the passenger info in regular trips is stored
 * @param dropOffs[][]     array containing full names of drop-off points
 */
void
searchPassenger(struct TripInfo trip[],
                struct Card passengers[][SPECIAL_PASS],
                stringDropOff dropOffs[][MAX_DROPOFFS])
{
    int i, j;
    int found = 0;
    stringName searchName;
    stringFullName fullName;
    stringDropOff origin = "";
    
    printSearchPassengerTitle();
    printf("Please enter the last name (No spaces, max 20 characters): ");
    scanf("%20s", searchName);
    clearInputBuffer();

    cls();
    printSearchPassengerTitle();

    for(i = 0; i < MAX_BUS; i++)
    {
        for(j = 0; j < SPECIAL_PASS; j++)
        {
            if(compareStrings(passengers[i][j].lastName, searchName) == 0)
            {
                // Trip number
                printf("Trip No:        %s\n", trip[i].tripNumber);

                // Priority number
                printf("Priority No:    %d\n", passengers[i][j].priorityNo);

                // Full name
                strcat(strcat(strcpy(fullName, passengers[i][j].lastName), ", "), passengers[i][j].firstName);
                printf("Full Name:      %s\n", fullName);

                // ID number
                printf("ID Number:      %d\n", passengers[i][j].idNo);

                // Embarkation point
                if(trip[i].dropOffSet == 0 || trip[i].dropOffSet == 1)
                {
                    strcpy(origin, "DLSU Manila Campus");
                }
                else if(trip[i].dropOffSet == 2 || trip[i].dropOffSet == 3)
                {
                    strcpy(origin, "DLSU Laguna Campus");
                }
                
                printf("From:           %s\n", origin);

                // Drop-off point
                printf("To:             %s\n\n", dropOffs[trip[i].dropOffSet][passengers[i][j].dropOff - 1]);

                found++;
            }
        }
    }

    if(found > 0)
        printf("%d passenger/s with last name \"%s\" found.\n\n", found, searchName);
    else
        printf("Passenger \"%s\" was not found.\n\n", searchName);

    pressAnyKey();
    cls();
}

/**
 * Asks for the file name and displays all the contents in the selected file.
 * 
 * @param trip[]           array containing trip information (trip number, etc.)
 * @param passengers[][]   array where the passenger info in regular trips is stored
 * @param dropOffs[][]     array containing full names of drop-off points
 */
void
displayRecentTrip()
{
    FILE *file;
    stringFileName fileName;
    struct FilePassenger temp;
    struct Date date = {0, 0, 0};

    // Ask user for the date
    printLoadRecentTripTitle();
    date = getDate();
    
    // Write the date info into a fileName string
    sprintf(fileName, "Trip-%02d-%02d-%04d.txt", date.dd, date.mm, date.yyyy);

    file = fopen(fileName, "r");

    if(file == NULL)
    {
        printLoadRecentTripTitle();
        printf("\033[0;31mERROR:\033[0m File not found/empty.\n\n");
    }
    else
    {
            printLoadRecentTripTitle();
            printf("Passenger information from file %s\n\n", fileName);
        
            while(fgets(temp.tripNumber, 6, file) != NULL)
            {
                fgetc(file);
                printf("%-16s%s\n", "Trip No:", temp.tripNumber);
                
                fgets(temp.origin, 21, file);
                // fgetc(file);
                printf("%-16s%s", "Origin:", temp.origin);
                
                fgets(temp.fullName, 44, file);
                // fgetc(file);
                printf("%-16s%s", "Full Name:", temp.fullName);
                
                fscanf(file, "%d", &temp.idNo);
                fgetc(file);
                printf("%-16s%08d\n", "ID Number:", temp.idNo);
                
                fscanf(file, "%d", &temp.priorityNo);
                fgetc(file);
                printf("%-16s%d\n", "Priority No:", temp.priorityNo);
                
                fgets(temp.dropOff, 41, file);
                fgetc(file);
                printf("%-16s%s\n", "Drop-off:", temp.dropOff);
            }
        
            fclose(file);
    }

    pressAnyKey();
    cls();
}
