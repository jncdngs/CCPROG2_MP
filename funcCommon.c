#include <stdio.h>
#include <conio.h>  // for getch()
#include <string.h>
#include "donguinesArrows.h"

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

void
copyStruct(struct Card *dest,
           struct Card *src)
{
    *dest = *src;
}

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
    int maxDays[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Ask user for date
    printf("Please enter the date for the filename.\n\n");
    
    do
    {
        printf("Month (mm): ");
        if(scanf("%d", &date.mm) != 1)
        {
            // Prevent loop when entering char
            clearInputBuffer();
            
            // Display error when option is a char/str
            printError();
        }
        else if(date.mm < 1 || date.mm > 12)
        {
            printError();
        }
    }
    while(date.mm < 1 || date.mm > 12);
    
    do
    {
        printf("Day (dd): ");
        if(scanf("%d", &date.dd) != 1)
        {
            // Prevent loop when entering char
            clearInputBuffer();
            
            // Display error when option is a char/str
            printError();
        }
        else if(date.dd < 1 || date.dd > maxDays[date.mm - 1])
        {
            printError();
        }
    }
    while(date.dd < 1 || date.dd > maxDays[date.mm - 1]);

    do
    {
        printf("Year (yyyy): ");
        if(scanf("%d", &date.yyyy) != 1)
        {
            // Prevent loop when entering char
            clearInputBuffer();
            
            // Display error when option is a char/str
            printError();
        }
        else if(date.yyyy < 1900 || date.yyyy > 2025)
        {
            printError();
        }
    }
    while (date.yyyy < 1900 || date.yyyy > 2025);
    
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
