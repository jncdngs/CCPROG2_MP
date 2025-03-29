#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "donguinesArrows.h"

/**
 * Initializes the struct arrays to "empty" to avoid garbage values.
 * Initializes priority numbers to 99 for sorting.
 * 
 * @param passengers[][]    array where all the passenger info is stored
 */
void
initializePassengers(struct Card passengers[][SPECIAL_PASS])
{
    int i, j;

    for(i = 0; i < MAX_BUS; i++)
    {
        for(j = 0; j < SPECIAL_PASS; j++)
        {
            passengers[i][j].priorityNo = 99;
            strcpy(passengers[i][j].lastName, "");
            strcpy(passengers[i][j].firstName, "");
            passengers[i][j].idNo = 0;
            passengers[i][j].dropOff = 0;
        }
    }
}

/**
 * Checks if the string tripNo is valid and in the trip array and returns the index in the array if found.
 * 
 * @param trip[]            array containing trip information (trip number, etc.)
 * @param tripNo            trip number to find in the array (AE101, etc.)
 * @return                  the index of the trip number in the trip array if found in regular trips, 
 *                          -1 if not found
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
 * Checks if ID number is valid and unique.
 * 
 * @param passengers[][]    array where all the passenger info is stored
 * @param idNo              ID number to be checked
 * @return                  0 if the ID number is invalid, 
 *                          1 if the ID number is valid and unique, 
 *                          2 if the ID number is valid but not unique
 */
int
isValidID(struct Card passengers[][SPECIAL_PASS],
          int idNo)
{
    int i, j;
    int valid = 0;

    // Check if in valid range
    if(idNo > 0 && idNo <= 99999999)
    {   
        valid = 1;

        // Check if unique
        for(i = 0; i < MAX_BUS; i++)
            for(j = 0; j < SPECIAL_PASS; j++)
                if(idNo == passengers[i][j].idNo)
                    valid = 2;
    }
    
    return valid;
}

/**
 * Checks if the chosen trip is full by comparing the priority level of the last passenger.
 * 
 * @param tripIndex         the index of the trip number to use
 * @param passengers[][]    array where all the passenger info is stored
 * @param priorityNo        priority number of the new passenger
 * @return                  0 if the trip is not full, 
 *                          1 if the passenger has higher priority, 
 *                          2 if the passenger has lower priority
 */
int
isFullTrip(int tripIndex,
           struct Card passengers[][SPECIAL_PASS],
           int priorityNo)
{
    int isFull;

    if(passengers[tripIndex][SPECIAL_PASS - 1].priorityNo == 99)
        isFull = 0;
    else if(passengers[tripIndex][SPECIAL_PASS - 1].priorityNo > priorityNo)
        isFull = 1;
    else
        isFull = 2;

    return isFull;
}

/**
 * Checks if a special trip has been deployed.
 * 
 * @param passengers[][]    array where all the passenger info is stored
 * @return                  0 if no special trip was deployed, 
 *                          1 if only SPEC1 has been deployed, 
 *                          2 if only SPEC2 has been deployed
 */
int
isSpecDeployed(struct Card passengers[][SPECIAL_PASS])
{
    int deploy = 0;

    if(passengers[9][0].priorityNo != 99)
        deploy++;
    if(passengers[21][0].priorityNo != 99)
        deploy += 2;

    return deploy;
}

/**
 * Converts the drop-off point of a passenger when moved to another trip.
 * 
 * @param dropOffOld        drop-off number to be converted
 * @param dropOffSetOld     drop-off set of the old trip 
 * @param dropOffSetNew     drop-off set of the new trip 
 * @return                  converted drop-off point number 
 */
int
convertDropOff(int dropOffOld,
               int dropOffSetOld,
               int dropOffSetNew)
{
    int dropOffNew = dropOffOld;
    
    // Check if drop-off sets are different
    if(dropOffSetOld != dropOffSetNew)
    {
        // Convert from set 0 to 1
        if(dropOffSetOld == 0)
            dropOffNew = 2;

        // Convert from set 1 to 0
        else if(dropOffSetOld == 1)
            dropOffNew = 3;

        // Convert from set 2 to 3 or set 3 to 2
        else if(dropOffSetOld == 2 || dropOffSetOld == 3)
            if(dropOffOld == 1)
                dropOffNew = 4;
    }

    return dropOffNew;
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
compareStrings(char *string1,
               char *string2)
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
 * Copies all elements of one Card struct to another.
 * 
 * @param *dest     pointer to the destination struct
 * @param *src      pointer to the original struct
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
 * @param passengers[][]    array where all the passenger info is stored
 * @param tripIndex         the index of the trip number to use
 * @param temp              Card struct containing the information of the passenger to be inserted
 */
void
insertPassenger(struct Card passengers[][SPECIAL_PASS],
                int tripIndex,
                struct Card temp)
{
    int i;
        
    for(i = SPECIAL_PASS - 1; i >= 0; i--)
    {
        if(temp.priorityNo < passengers[tripIndex][i].priorityNo)
        {
            if(i == SPECIAL_PASS - 1)
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
 * Finds the next available trip and shifts last passengers accordingly
 * 
 * @param trip[]            array containing trip information (trip number, etc.)
 * @param passengers[][]    array where all the passenger info is stored
 * @param tripIndex         the index of the trip number to use
 */
void
movePassenger(struct TripInfo trip[],
              struct Card passengers[][SPECIAL_PASS],
              int tripIndex)
{
    int i = tripIndex;
    int tripAvail = -1;
    int lastTrip = -1;

    // Assign last trip index to check based on route
    if(tripIndex < 9)
        lastTrip = 9;
    else
        lastTrip = 21;

    // Find next trip with vacant seat/s
    while(i <= lastTrip && tripAvail == -1)
    {
        // Check if last seat in next trip
        if(passengers[i][SPECIAL_PASS - 1].priorityNo == 99)
            tripAvail = i;
        
        i++;
    }

    // Shift last passengers from tripAvail backwards       
    if(tripAvail != -1)
    {
        for(i = tripAvail; i >= tripIndex; i--)
        {
            // Insert the passenger to the new trip
            insertPassenger(passengers, i, passengers[i - 1][SPECIAL_PASS - 1]);
            
            // Convert the drop-off point of the passenger
            passengers[i][SPECIAL_PASS - 1].dropOff = convertDropOff(passengers[i - 1][SPECIAL_PASS - 1].dropOff,
                                                                     trip[i - 1].dropOffSet,
                                                                     trip[i].dropOffSet);
        }
    }
}

/**
 * Displays the trip number, time, and origin of each trip in the trip array.
 * 
 * @param trip[]        array containing trip information (trip number, etc.)
 * @param specDeployed  flag that specifies if special trips were deployed
 */
void
displayTrips(struct TripInfo trip[],
             int specDeployed)
{
    int i;
    int rowsMax = 12;
    int firstRouteCount = 10;
    int spec1 = 0;
    int spec2 = 0;
    
    printf("%-10s%-9s%-28s", "Trip", "Time", "Origin");
    printf("%-10s%-9s%s\n\n", "Trip", "Time", "Origin");

    for(i = 0; i < rowsMax; i++)
    {
        // Display trips from first route (first 3 columns)
        if((trip[i].dropOffSet == 0 || 
            trip[i].dropOffSet == 1) && 
            i != 9)
            printf("%-10s%-9s%-28s", trip[i].tripNumber,
                                     trip[i].tripTime,
                                     trip[i].tripOrigin);
        // Print SPEC1 if deployed
        else if((specDeployed == 1 || specDeployed == 3) && !spec1)
        {    
            printf("%-10s%-9s%-28s", trip[9].tripNumber,
                                     trip[9].tripTime,
                                     trip[9].tripOrigin);
            spec1++;
        }
        // Print spaces if first route has less trips than second route
        else
            printf("%47s", "");

        // Display trips from second route (next 3 columns)
        if((trip[i + firstRouteCount].dropOffSet == 2 || 
            trip[i + firstRouteCount].dropOffSet == 3) && 
            i + firstRouteCount != 21)
            printf("%-10s%-9s%s\n", trip[i + firstRouteCount].tripNumber,
                                    trip[i + firstRouteCount].tripTime,
                                    trip[i + firstRouteCount].tripOrigin);
        // Print SPEC2 if deployed
        else if((specDeployed == 2 || specDeployed == 3) && !spec2)
        {
            printf("%-10s%-9s%s\n", trip[21].tripNumber,
                                    trip[21].tripTime,
                                    trip[21].tripOrigin);
            spec2++;
        }
    }

    printf("\n");
}

/**
 * Displays the list of drop-offs in the given trip and number of passenger getting off.
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
 * @param passengers[][]    array where all the passenger info is stored
 * @param dropOffs[][]      array containing full names of drop-off points
 * @param passengerCount[]  passenger count for each drop-off point
 */
void
displayDropOffCount(struct TripInfo trip[],
                    int tripIndex,
                    struct Card passengers[][SPECIAL_PASS],
                    stringDropOff dropOffs[][MAX_DROPOFFS],
                    int passengerCount[])
{
    int i, j;

    // Count number of passengers for each drop-off point
    for(i = 0; i < SPECIAL_PASS; i++)
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
struct Date
getDate()
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
 * Saves information of all saved passengers to a text file
 * 
 * @param trip[]            array containing trip information (trip number, etc.)
 * @param passengers[][]    array where all the passenger info is stored
 * @param dropOffs[][]      array containing full names of drop-off points
 */
void
savePassengerInfo(struct TripInfo trip[],
                  struct Card passengers[][SPECIAL_PASS],
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
        for(j = 0; j < SPECIAL_PASS; j++)
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
    
    fclose(file);

    cls();
    printTitle();
    printf("Saved to file %s\n\n", fileName);
    printf("Thank you for using the Arrows Express Embarkation System!\n\n");
    printf("Press any key to exit...");
    getch();
}
