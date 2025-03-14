#include <stdio.h>
#include <conio.h>  // for getch()
#include <string.h>
#include "donguinesArrows.h"

void
initializePassengers(struct Card passengers[][MAX_PASS])
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
}

int
isValidTrip(struct TripInfo trip[],
            stringTrip tripNo)
{
    int i;
    int tripIndex = -1;

    for(i = 0; i < MAX_BUS; i++)
    {
        if(compareStrings(trip[i].tripNumber, tripNo) == 0)
        {
            tripIndex = i;
        }
    }

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
    {
        if(passengers[tripIndex][i].priorityNo != 99)
        {
            passengerCount++;
        }
    }

    if(passengerCount == MAX_PASS)
    {
        isFull = 1;
    }

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

    while((string1[i] != '\0' || string2[i] != '\0') && diff == 0)
    {
        char1 = string1[i];
        char2 = string2[i];

        if(char1 >= 'a' && char1 <= 'z')
        {
            char1 -= 32;
        }

        if(char2 >= 'a' && char2 <= 'z')
        {
            char2 -= 32;
        }

        if(diff == 0)
        {
            diff = char1 - char2;
        }

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
            {
                copyStruct(&passengers[tripIndex][i], &temp);
            }
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
    
    printf("%-10s%-9s%-17s", "Trip", "Time", "Route");
    printf("%-10s%-9s%s\n\n", "Trip", "Time", "Route");

    for(i = 0; i < rowsMax; i++)
    {
        // Display trips from first route (first 3 columns)
        if(trip[i].dropOffSet == 0 || trip[i].dropOffSet == 1)
        {
            printf("%-10s%-9s%-17s", trip[i].tripNumber,
                                     trip[i].tripTime,
                                     trip[i].tripRoute);
        }
        else    // Print spaces if first route has less trips than second route
        {
            printf("%36s", "");
        }

        // Display trips from second route (next 3 columns)
        if(trip[i + firstRouteCount].dropOffSet == 2 || trip[i + firstRouteCount].dropOffSet == 3)
        {
            printf("%-10s%-9s%s\n", trip[i + firstRouteCount].tripNumber,
                                    trip[i + firstRouteCount].tripTime,
                                    trip[i + firstRouteCount].tripRoute);
        }
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
        {
            i = MAX_DROPOFFS;
        }
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
    {      
        for(j = 0; j < MAX_DROPOFFS; j++)
        {
            if(passengers[tripIndex][i].dropOff - 1 == j)
            {
                passengerCount[j]++;
            }
        }
    }

    // Display list of drop-off points with passenger count
    for(i = 0; i < MAX_DROPOFFS; i++)
    {       
        printf("%-36s%d\n", dropOffs[trip[tripIndex].dropOffSet][i],
                            passengerCount[i]);

        // Break the loop if all available drop-off points have been displayed
        if(compareStrings(dropOffs[trip[tripIndex].dropOffSet][i + 1], "") == 0)
        {
            i = MAX_DROPOFFS;
        }
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
    stringFullName fullName;

    file = fopen("test.txt", "a");

    for(i = 0; i < MAX_BUS; i++)
    {
        for(j = 0; j < MAX_PASS; j++)
        {
            if(passengers[i][j].priorityNo != 99)
            {
                // Trip number
                fprintf(file, "%s\n", trip[i].tripNumber);

                // Embarkation point
                if(trip[i].dropOffSet == 0 || trip[i].dropOffSet == 1)
                {
                    fprintf(file, "DLSU Manila Campus\n");
                }
                else if(trip[i].dropOffSet == 2 || trip[i].dropOffSet == 3)
                {
                    fprintf(file, "DLSU Laguna Campus\n");
                }

                // Passenger name
                strcat(strcat(strcpy(fullName, passengers[i][j].lastName), ", "), passengers[i][j].firstName);
                fprintf(file, "%s\n", fullName);

                // ID number
                fprintf(file, "%d\n", passengers[i][j].idNo);

                // Priority number
                fprintf(file, "%d\n", passengers[i][j].priorityNo);

                // Drop-off point
                fprintf(file, "%d - %s\n\n", passengers[i][j].dropOff, 
                                             dropOffs[trip[i].dropOffSet][passengers[i][j].dropOff - 1]);
            }
        }
    }

    fclose(file);
}
