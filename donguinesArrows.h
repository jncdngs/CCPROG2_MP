#ifndef DONGUINES_ARROWS_H
#define DONGUINES_ARROWS_H

#define MAX_CHARS 51    // Maximum of 50 chars each for last name and first name
#define MAX_PASS 13     // Maximum of 13 passengers per regular shuttle
#define MAX_BUS 20      // Maximum of 20 regular shuttles

typedef char stringTrip[6];
typedef char stringDropOff[4];
typedef char stringName[51];

struct Card
{
    int priorityNo;
    stringName lastName;
    stringName firstName;
    int idNo;
    int dropOff;
};

void cls();
void clearInputBuffer();

void printError();
void printTitle();
void printPassengerTitle();
void printPassengerInfoTitle();
void printDivider();

void initializePassengers(struct Card passengers[][MAX_PASS]);
int isValidTrip(stringTrip trip[MAX_BUS], stringTrip tripNo);
int isFullTrip(int tripIndex, struct Card passengers[][MAX_PASS]);
void enterPassengerInfo(stringTrip trip[MAX_BUS], struct Card passengers[][MAX_PASS]);

#endif
