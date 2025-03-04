#ifndef DONGUINES_ARROWS_H
#define DONGUINES_ARROWS_H

#define MAX_CHARS 21    // Maximum of 20 chars each for last name and first name
#define MAX_PASS 13     // Maximum of 13 passengers per regular shuttle
#define MAX_BUS 20      // Maximum of 20 regular shuttles
#define MAX_DROPOFFS 4  // Maximum of 4 drop-off points per shuttle

typedef char stringTrip[6];                     // "AE101", etc.
typedef char stringTime[5];                     // "0600", etc.
typedef char stringRoute[8];                    // "MNL-LAG", "LAG-MNL"
typedef char stringDropOff[41];                 // Full drop-off point name
typedef char stringName[MAX_CHARS];             // Passenger name
typedef char stringFullName[MAX_CHARS * 2 + 2]; // Full name

struct TripInfo
{
    stringTrip tripNumber;
    stringTime tripTime;
    stringRoute tripRoute;
    int dropOffSet;
};

struct Card
{
    int priorityNo;
    stringName lastName;
    stringName firstName;
    int idNo;
    int dropOff;
};

// funcDisplay.c
void cls();
void clearInputBuffer();
void pressAnyKey();
void printError();
void printTitle();
void printPassengerTitle();
void printPassengerInfoTitle();
void printPersonnelTitle();
void printPassengerCountTitle();
void printDropOffTitle();

// funcCommon.c
void initializePassengers(struct Card[][MAX_PASS]);
int isValidTrip(struct TripInfo[], stringTrip);
int isFullTrip(int, struct Card[][MAX_PASS]);
int getEmptySeat(int, struct Card[][MAX_PASS]);
/* void swapStruct(struct Card*, struct Card*); */
void copyStruct(struct Card*, struct Card*);
void insertPassenger(struct Card[][MAX_PASS], int, struct Card);
void displayTrips(struct TripInfo[]);
void displayDropOffs(struct TripInfo[], int, stringDropOff[][MAX_DROPOFFS]);
void displayDropOffCount(struct TripInfo[], int, struct Card[][MAX_PASS], stringDropOff[][MAX_DROPOFFS], int[]);

// funcPassenger.c
void enterPassengerInfo(struct TripInfo[], struct Card[][MAX_PASS], stringDropOff[][MAX_DROPOFFS]);

// funcPersonnel.c
void viewPassengerCount(struct TripInfo[], struct Card[][MAX_PASS]);
void viewDropOffCount(struct TripInfo[], struct Card[][MAX_PASS], stringDropOff[][MAX_DROPOFFS]);
void viewPassengerInfo(struct TripInfo[], struct Card[][MAX_PASS]);

#endif
