#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "donguinesArrows.h"

/**
 * Initializes the struct arrays to "empty" to avoid garbage values.
 * Initializes priority numbers to 99 for sorting.
 * 
 * @param passengers[][]            array where the passenger info in regular trips is stored
 * @param passengersSpecial[][]     array where the passenger info in special trips is stored
 */
void
initializePassengers(struct Card passengers[][MAX_PASS],
                     struct Card passengersSpecial[][SPECIAL_PASS])
{
    int i, j;

    for(i = 0; i < MAX_BUS; i++)
    {
        for(j = 0; j < MAX_PASS; j++)
        {
            passengers[i][j].priorityNo = 99;
            strcpy(passengers[i][j].lastName, "");
            strcpy(passengers[i][j].firstName, "");
            passengers[i][j].idNo = 0;
            passengers[i][j].dropOff = 0;
        }
    }

    for(i = 0; i < SPECIAL_BUS; i++)
    {
        for(j = 0; j < SPECIAL_PASS; j++)
        {
            passengersSpecial[i][j].priorityNo = 99;
            strcpy(passengersSpecial[i][j].lastName, "");
            strcpy(passengersSpecial[i][j].firstName, "");
            passengersSpecial[i][j].idNo = 0;
            passengersSpecial[i][j].dropOff = 0;
        }
    }
}

/**
 * Checks if the string tripNo is in the trip array and returns the index in the array if found.
 * 
 * @param trip[]    array containing trip information (trip number, etc.)
 * @param tripNo    trip number to find in the array (AE101, etc.)
 * @return          the index of the trip number in the trip array if found, -1 if not found
 */
int
isValidTrip(struct TripInfo trip[],
            stringTrip tripNo)
{
    int i;
    int tripIndex = -1;

    for(i = 0; i < MAX_BUS; i++)
        if(compareStrings(trip[i].tripNumber, tripNo) == 0)
            tripIndex = i;

    return tripIndex;
}

/**
 * Checks if the chosen trip is full.
 * 
 * @param tripIndex         the index of the trip number to use
 * @param passengers[][]    array where the passenger info in regular trips is stored
 * @return                  1 if the trip is full, 0 if not full
 */
int
isFullTrip(int tripIndex,
           struct Card passengers[][MAX_PASS])
{
    int i;
    int passengerCount = 0;
    int isFull = 0;

    for(i = 0; i < MAX_PASS; i++)
        if(passengers[tripIndex][i].priorityNo != 99)
            passengerCount++;

    if(passengerCount == MAX_PASS)
        isFull = 1;

    return isFull;
}

/**
 * Finds the first empty seat in the selected trip.
 * 
 * @param tripIndex         the index of the trip number to use
 * @param passengers[][]    array where the passenger info in regular trips is stored
 * @return                  the index of the seat in the passengers array if found, -1 if not found
 */
int
getEmptySeat(int tripIndex,
             struct Card passengers[][MAX_PASS])
{
    int i;
    int emptySeat = -1;

    for(i = 0; i < MAX_PASS; i++)
    {
        if(passengers[tripIndex][i].priorityNo == 99)
        {
            emptySeat = i;
            i = MAX_PASS;
        }
    }

    return emptySeat;
}

/**
 * Converts two strings to UPPERCASE and compares them.
 * Works like strcmp() but is case-insensitive.
 * 
 * @param *string1      pointer to the first string to be compared
 * @param *string2      pointer to the second string to be compared
 * @return              difference between the two strings, 0 if similar
 */
int
compareStrings(char *string1, char *string2)
{
    char char1, char2;
    int i = 0;
    int diff = 0;

    // Loop until reached end of string or found difference
    while((string1[i] != '\0' || string2[i] != '\0') && diff == 0)
    {
        char1 = string1[i];
        char2 = string2[i];

        // If character is lowercase, convert to uppercase
        if(char1 >= 'a' && char1 <= 'z')
            char1 -= 32;

        // If character is lowercase, convert to uppercase
        if(char2 >= 'a' && char2 <= 'z')
            char2 -= 32;

        // Get the difference between the two characters
        diff = char1 - char2;

        i++;
    }

    return diff;
}

/**
 * Copies all elements of one struct to another.
 * 
 * @param *dest     pointer to the struct to copy into
 * @param *src      pointer to the original struct to be copied
 */
void
copyStruct(struct Card *dest,
           struct Card *src)
{
    *dest = *src;
}

/**
 * Inserts passenger info to the given trip based on priority number.
 * 
 * @param passengers[][]    array where the passenger info in regular trips is stored
 * @param tripIndex         the index of the trip number to use
 * @param temp              struct containing the information of the passenger to be inserted
 */
void
insertPassenger(struct Card passengers[][MAX_PASS],
                int tripIndex,
                struct Card temp)
{
    int i;
    
    for(i = MAX_PASS - 1; i >= 0; i--)
    {
        if(temp.priorityNo < passengers[tripIndex][i].priorityNo)
        {
            if(i == MAX_PASS - 1)
                copyStruct(&passengers[tripIndex][i], &temp);
            else
            {
                copyStruct(&passengers[tripIndex][i + 1], &passengers[tripIndex][i]);
                copyStruct(&passengers[tripIndex][i], &temp);
            }
        }
    }
}

/**
 * Displays the trip number, time, and origin of each trip in the trip array.
 * 
 * @param trip[]    array containing trip information (trip number, etc.)
 */
void
displayTrips(struct TripInfo trip[])
{
    int i;
    int rowsMax = 11;
    int firstRouteCount = 9;
    
    printf("%-10s%-9s%-28s", "Trip", "Time", "Origin");
    printf("%-10s%-9s%s\n\n", "Trip", "Time", "Origin");

    for(i = 0; i < rowsMax; i++)
    {
        // Display trips from first route (first 3 columns)
        if(trip[i].dropOffSet == 0 || trip[i].dropOffSet == 1)
            printf("%-10s%-9s%-28s", trip[i].tripNumber,
                                     trip[i].tripTime,
                                     trip[i].tripOrigin);
        else    // Print spaces if first route has less trips than second route
            printf("%47s", "");

        // Display trips from second route (next 3 columns)
        if(trip[i + firstRouteCount].dropOffSet == 2 || trip[i + firstRouteCount].dropOffSet == 3)
            printf("%-10s%-9s%s\n", trip[i + firstRouteCount].tripNumber,
                                    trip[i + firstRouteCount].tripTime,
                                    trip[i + firstRouteCount].tripOrigin);
    }

    printf("\n");
}

/**
 * Displays the trip number, time, and origin of each trip in the trip array.
 * 
 * @param trip[]        array containing trip information (trip number, etc.)
 * @param tripIndex     the index of the trip number to use
 * @param dropOffs[][]  array containing full names of drop-off points
 */
void
displayDropOffs(struct TripInfo trip[],
                int tripIndex,
                stringDropOff dropOffs[][MAX_DROPOFFS])
{
    int i;

    for(i = 0; i < MAX_DROPOFFS; i++)
    {
        printf("[%d] %s\n", i + 1, dropOffs[trip[tripIndex].dropOffSet][i]);

        // Break the loop if all available drop-off points have been displayed
        if(compareStrings(dropOffs[trip[tripIndex].dropOffSet][i + 1], "") == 0)
            i = MAX_DROPOFFS;
    }

    printf("\n");
}

/**
 * Displays the full name of valid drop-off points in given trip and number of passengers getting off in each.
 * 
 * @param trip[]            array containing trip information (trip number, etc.)
 * @param tripIndex         the index of the trip number to use
 * @param passengers[][]    array where the passenger info in regular trips is stored
 * @param dropOffs[][]      array containing full names of drop-off points
 * @param passengerCount[]  passenger count for each drop-off point
 */
void
displayDropOffCount(struct TripInfo trip[],
                    int tripIndex,
                    struct Card passengers[][MAX_PASS],
                    stringDropOff dropOffs[][MAX_DROPOFFS],
                    int passengerCount[])
{
    int i, j;

    // Count number of passengers for each drop-off point
    for(i = 0; i < MAX_PASS; i++)
        for(j = 0; j < MAX_DROPOFFS; j++)
            if(passengers[tripIndex][i].dropOff - 1 == j)
                passengerCount[j]++;

    // Display list of drop-off points with passenger count
    for(i = 0; i < MAX_DROPOFFS; i++)
    {       
        printf("%-36s%d\n", dropOffs[trip[tripIndex].dropOffSet][i],
                            passengerCount[i]);

        // Break the loop if all available drop-off points have been displayed
        if(compareStrings(dropOffs[trip[tripIndex].dropOffSet][i + 1], "") == 0)
            i = MAX_DROPOFFS;
    }

    printf("\n");
}

/**
 * Ask user for valid month, day, and year.
 * 
 * @return struct containing the month, day, and year
 */
struct Date getDate()
{
    struct Date dateTemp = {0, 0, 0};
    
    int maxDays[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Ask user for date
    printf("Please enter the date for the filename.\n\n");
    
    do
    {
        printf("Month (mm): ");
        if(scanf("%d", &dateTemp.mm) != 1)
        {
            // Prevent loop when entering char
            clearInputBuffer();
            
            // Display error when option is a char/str
            printError();
        }
        else if(dateTemp.mm < 1 || dateTemp.mm > 12)
        {
            printError();
        }
    }
    while(dateTemp.mm < 1 || dateTemp.mm > 12);
    
    do
    {
        printf("Day (dd): ");
        if(scanf("%d", &dateTemp.dd) != 1)
        {
            // Prevent loop when entering char
            clearInputBuffer();
            
            // Display error when option is a char/str
            printError();
        }
        else if(dateTemp.dd < 1 || dateTemp.dd > maxDays[dateTemp.mm - 1])
        {
            printError();
        }
    }
    while(dateTemp.dd < 1 || dateTemp.dd > maxDays[dateTemp.mm - 1]);

    do
    {
        printf("Year (yyyy): ");
        if(scanf("%d", &dateTemp.yyyy) != 1)
        {
            // Prevent loop when entering char
            clearInputBuffer();
            
            // Display error when option is a char/str
            printError();
        }
        else if(dateTemp.yyyy < 1900 || dateTemp.yyyy > 2025)
        {
            printError();
        }
    }
    while (dateTemp.yyyy < 1900 || dateTemp.yyyy > 2025);

    cls();

    return dateTemp;
}

/**
 * Saves information of all passengers to a text file
 * 
 * @param trip[]            array containing trip information (trip number, etc.)
 * @param passengers[][]    array where the passenger info in regular trips is stored
 * @param dropOffs[][]      array containing full names of drop-off points
 */
void
savePassengerInfo(struct TripInfo trip[],
                  struct Card passengers[][MAX_PASS],
                  stringDropOff dropOffs[][MAX_DROPOFFS])
{
    FILE *file;
    int i, j;
    stringFileName fileName;
    stringFullName fullName;
    struct Date date = {0, 0, 0};

    // Ask user for the date
    date = getDate();
    
    // Write the date info into a fileName string
    sprintf(fileName, "Trip-%02d-%02d-%04d.txt", date.dd, date.mm, date.yyyy);

    file = fopen(fileName, "w");

    for(i = 0; i < MAX_BUS; i++)
    {
        for(j = 0; j < MAX_PASS; j++)
        {
            if(passengers[i][j].priorityNo != 99)
            {
                // Trip number
                fprintf(file, "%s\n", trip[i].tripNumber);

                // Embarkation point
                fprintf(file, "%s\n", trip[i].tripOrigin);

                // Passenger name
                strcat(strcat(strcpy(fullName, passengers[i][j].lastName), ", "), passengers[i][j].firstName);
                fprintf(file, "%s\n", fullName);

                // ID number
                fprintf(file, "%08d\n", passengers[i][j].idNo);

                // Priority number
                fprintf(file, "%d\n", passengers[i][j].priorityNo);

                // Drop-off point
                fprintf(file, "%d - %s\n\n", passengers[i][j].dropOff, 
                                             dropOffs[trip[i].dropOffSet][passengers[i][j].dropOff - 1]);
            }
        }
    }

    cls();
    printTitle();
    printf("Saved to file %s\n\n", fileName);
    printf("Thank you for using the Arrows Express Embarkation System!\n\n");
    printf("Press any key to exit...");
    getch();

    // Save special shuttle info

    fclose(file);
}
