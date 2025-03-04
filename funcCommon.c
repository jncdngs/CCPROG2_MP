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
            passengers[i][j].priorityNo = 0;
            strcpy(passengers[i][j].lastName, "");
            strcpy(passengers[i][j].firstName, "");
            passengers[i][j].idNo = 0;
            passengers[i][j].dropOff = -1;
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
        if(strcmp(trip[i].tripNumber, tripNo) == 0)
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
        if(passengers[tripIndex][i].priorityNo != 0)
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
    int found = 0;
    int emptySeat = -1;

    for(i = 0; i < MAX_PASS; i++)
    {
        if(passengers[tripIndex][i].priorityNo == 0 && !found)
        {
            emptySeat = i;
            found = 1;
        }
    }

    return emptySeat;
}

void
swapStruct(struct Card *passenger1,
           struct Card *passenger2)
{
    struct Card temp;

    temp = *passenger1;
    *passenger1 = *passenger2;
    *passenger2 = temp;
}

void
insertPassenger()
{
    
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
        if(strcmp(dropOffs[trip[tripIndex].dropOffSet][i + 1], "") == 0)
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
        if(strcmp(dropOffs[trip[tripIndex].dropOffSet][i + 1], "") == 0)
        {
            i = MAX_DROPOFFS;
        }
    }

    printf("\n");
}
